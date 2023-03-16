/* Code to save the iptables state, in human readable-form. */
/* (C) 1999 by Paul 'Rusty' Russell <rusty@rustcorp.com.au> and
 * (C) 2000-2002 by Harald Welte <laforge@gnumonks.org>
 *
 * This code is distributed under the terms of GNU GPL v2
 *
 */
#include <getopt.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <netdb.h>
#include <unistd.h>
#include "libiptc/libiptc.h"
#include "libiptc/libip6tc.h"
#include "iptables.h"
#include "ip6tables.h"
#include "iptables-multi.h"
#include "ip6tables-multi.h"
#include "xshared.h"

static int show_counters;

static const struct option options[] = {
	{.name = "counters", .has_arg = false, .val = 'c'},
	{.name = "dump",     .has_arg = false, .val = 'd'},
	{.name = "table",    .has_arg = true,  .val = 't'},
	{.name = "modprobe", .has_arg = true,  .val = 'M'},
	{.name = "file",     .has_arg = true,  .val = 'f'},
	{.name = "version",  .has_arg = false, .val = 'V'},
	{NULL},
};

struct iptables_save_cb {
	const struct xtc_ops *ops;

	void (*dump_rules)(const char *chain, struct xtc_handle *handle);
};

static int
for_each_table(int (*func)(struct iptables_save_cb *cb, const char *tablename),
	       struct iptables_save_cb *cb)
{
	int ret = 1;
	FILE *procfile = NULL;
	char tablename[XT_TABLE_MAXNAMELEN+1];

	procfile = fopen(afinfo->proc_exists, "re");
	if (!procfile) {
		if (errno == ENOENT)
			return ret;
		fprintf(stderr, "Failed to list table names in %s: %s\n",
		        afinfo->proc_exists, strerror(errno));
		exit(1);
	}

	while (fgets(tablename, sizeof(tablename), procfile)) {
		if (tablename[strlen(tablename) - 1] != '\n')
			xtables_error(OTHER_PROBLEM,
				   "Badly formed tablename `%s'\n",
				   tablename);
		tablename[strlen(tablename) - 1] = '\0';
		ret &= func(cb, tablename);
	}

	fclose(procfile);
	return ret;
}

static int do_output(struct iptables_save_cb *cb, const char *tablename)
{
	struct xtc_handle *h;
	const char *chain = NULL;

	if (!tablename)
		return for_each_table(&do_output, cb);

	h = cb->ops->init(tablename);
	if (h == NULL) {
		xtables_load_ko(xtables_modprobe_program, false);
		h = cb->ops->init(tablename);
	}
	if (!h)
		xtables_error(OTHER_PROBLEM, "Cannot initialize: %s\n",
			      cb->ops->strerror(errno));

	time_t now = time(NULL);

	printf("# Generated by %s v%s on %s",
	       xt_params->program_name, IPTABLES_VERSION, ctime(&now));
	printf("*%s\n", tablename);

	/* Dump out chain names first,
	 * thereby preventing dependency conflicts */
	for (chain = cb->ops->first_chain(h);
	     chain;
	     chain = cb->ops->next_chain(h)) {

		printf(":%s ", chain);
		if (cb->ops->builtin(chain, h)) {
			struct xt_counters count;

			printf("%s ", cb->ops->get_policy(chain, &count, h));
			printf("[%llu:%llu]\n",
			       (unsigned long long)count.pcnt,
			       (unsigned long long)count.bcnt);
		} else {
			printf("- [0:0]\n");
		}
	}

	for (chain = cb->ops->first_chain(h);
	     chain;
	     chain = cb->ops->next_chain(h)) {
		cb->dump_rules(chain, h);
	}

	now = time(NULL);
	printf("COMMIT\n");
	printf("# Completed on %s", ctime(&now));
	cb->ops->free(h);

	return 1;
}

/* Format:
 * :Chain name POLICY packets bytes
 * rule
 */
static int
do_iptables_save(struct iptables_save_cb *cb, int argc, char *argv[])
{
	const char *tablename = NULL;
	FILE *file = NULL;
	int ret, c;

	while ((c = getopt_long(argc, argv, "bcdt:M:f:V", options, NULL)) != -1) {
		switch (c) {
		case 'b':
			fprintf(stderr, "-b/--binary option is not implemented\n");
			break;
		case 'c':
			show_counters = 1;
			break;

		case 't':
			/* Select specific table. */
			tablename = optarg;
			break;
		case 'M':
			xtables_modprobe_program = optarg;
			break;
		case 'f':
			file = fopen(optarg, "w");
			if (file == NULL) {
				fprintf(stderr, "Failed to open file, error: %s\n",
					strerror(errno));
				exit(1);
			}
			ret = dup2(fileno(file), STDOUT_FILENO);
			if (ret == -1) {
				fprintf(stderr, "Failed to redirect stdout, error: %s\n",
					strerror(errno));
				exit(1);
			}
			fclose(file);
			break;
		case 'd':
			do_output(cb, tablename);
			exit(0);
		case 'V':
			printf("%s v%s (legacy)\n",
			       xt_params->program_name,
			       xt_params->program_version);
			exit(0);
		default:
			fprintf(stderr,
				"Look at manual page `%s.8' for more information.\n",
				xt_params->program_name);
			exit(1);
		}
	}

	if (optind < argc) {
		fprintf(stderr, "Unknown arguments found on commandline\n");
		exit(1);
	}

	return !do_output(cb, tablename);
}

#ifdef ENABLE_IPV4
static void iptables_dump_rules(const char *chain, struct xtc_handle *h)
{
	const struct ipt_entry *e;

	/* Dump out rules */
	e = iptc_first_rule(chain, h);
	while(e) {
		print_rule4(e, h, chain, show_counters);
		e = iptc_next_rule(e, h);
	}
}

struct iptables_save_cb ipt_save_cb = {
	.ops		= &iptc_ops,
	.dump_rules	= iptables_dump_rules,
};

/* Format:
 * :Chain name POLICY packets bytes
 * rule
 */
int
iptables_save_main(int argc, char *argv[])
{
	iptables_globals.program_name = "iptables-save";
	if (xtables_init_all(&iptables_globals, NFPROTO_IPV4) < 0) {
		fprintf(stderr, "%s/%s Failed to initialize xtables\n",
				iptables_globals.program_name,
				iptables_globals.program_version);
		exit(1);
	}
#if defined(ALL_INCLUSIVE) || defined(NO_SHARED_LIBS)
	init_extensions();
	init_extensions4();
#endif

	return do_iptables_save(&ipt_save_cb, argc, argv);
}
#endif /* ENABLE_IPV4 */

#ifdef ENABLE_IPV6
static void ip6tables_dump_rules(const char *chain, struct xtc_handle *h)
{
	const struct ip6t_entry *e;

	/* Dump out rules */
	e = ip6tc_first_rule(chain, h);
	while(e) {
		print_rule6(e, h, chain, show_counters);
		e = ip6tc_next_rule(e, h);
	}
}

struct iptables_save_cb ip6t_save_cb = {
	.ops		= &ip6tc_ops,
	.dump_rules	= ip6tables_dump_rules,
};

/* Format:
 * :Chain name POLICY packets bytes
 * rule
 */
int
ip6tables_save_main(int argc, char *argv[])
{
	ip6tables_globals.program_name = "ip6tables-save";
	if (xtables_init_all(&ip6tables_globals, NFPROTO_IPV6) < 0) {
		fprintf(stderr, "%s/%s Failed to initialize xtables\n",
				ip6tables_globals.program_name,
				ip6tables_globals.program_version);
		exit(1);
	}
#if defined(ALL_INCLUSIVE) || defined(NO_SHARED_LIBS)
	init_extensions();
	init_extensions6();
#endif

	return do_iptables_save(&ip6t_save_cb, argc, argv);
}
#endif /* ENABLE_IPV6 */
