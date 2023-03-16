#include <btrfsutil.h>
#include "btrfsutilpy.h"

void add_module_constants(PyObject *m)
{
	PyModule_AddIntConstant(m, "ERROR_STOP_ITERATION", BTRFS_UTIL_ERROR_STOP_ITERATION);
	PyModule_AddIntConstant(m, "ERROR_NO_MEMORY", BTRFS_UTIL_ERROR_NO_MEMORY);
	PyModule_AddIntConstant(m, "ERROR_INVALID_ARGUMENT", BTRFS_UTIL_ERROR_INVALID_ARGUMENT);
	PyModule_AddIntConstant(m, "ERROR_NOT_BTRFS", BTRFS_UTIL_ERROR_NOT_BTRFS);
	PyModule_AddIntConstant(m, "ERROR_NOT_SUBVOLUME", BTRFS_UTIL_ERROR_NOT_SUBVOLUME);
	PyModule_AddIntConstant(m, "ERROR_SUBVOLUME_NOT_FOUND", BTRFS_UTIL_ERROR_SUBVOLUME_NOT_FOUND);
	PyModule_AddIntConstant(m, "ERROR_OPEN_FAILED", BTRFS_UTIL_ERROR_OPEN_FAILED);
	PyModule_AddIntConstant(m, "ERROR_RMDIR_FAILED", BTRFS_UTIL_ERROR_RMDIR_FAILED);
	PyModule_AddIntConstant(m, "ERROR_UNLINK_FAILED", BTRFS_UTIL_ERROR_UNLINK_FAILED);
	PyModule_AddIntConstant(m, "ERROR_STAT_FAILED", BTRFS_UTIL_ERROR_STAT_FAILED);
	PyModule_AddIntConstant(m, "ERROR_STATFS_FAILED", BTRFS_UTIL_ERROR_STATFS_FAILED);
	PyModule_AddIntConstant(m, "ERROR_SEARCH_FAILED", BTRFS_UTIL_ERROR_SEARCH_FAILED);
	PyModule_AddIntConstant(m, "ERROR_INO_LOOKUP_FAILED", BTRFS_UTIL_ERROR_INO_LOOKUP_FAILED);
	PyModule_AddIntConstant(m, "ERROR_SUBVOL_GETFLAGS_FAILED", BTRFS_UTIL_ERROR_SUBVOL_GETFLAGS_FAILED);
	PyModule_AddIntConstant(m, "ERROR_SUBVOL_SETFLAGS_FAILED", BTRFS_UTIL_ERROR_SUBVOL_SETFLAGS_FAILED);
	PyModule_AddIntConstant(m, "ERROR_SUBVOL_CREATE_FAILED", BTRFS_UTIL_ERROR_SUBVOL_CREATE_FAILED);
	PyModule_AddIntConstant(m, "ERROR_SNAP_CREATE_FAILED", BTRFS_UTIL_ERROR_SNAP_CREATE_FAILED);
	PyModule_AddIntConstant(m, "ERROR_SNAP_DESTROY_FAILED", BTRFS_UTIL_ERROR_SNAP_DESTROY_FAILED);
	PyModule_AddIntConstant(m, "ERROR_DEFAULT_SUBVOL_FAILED", BTRFS_UTIL_ERROR_DEFAULT_SUBVOL_FAILED);
	PyModule_AddIntConstant(m, "ERROR_SYNC_FAILED", BTRFS_UTIL_ERROR_SYNC_FAILED);
	PyModule_AddIntConstant(m, "ERROR_START_SYNC_FAILED", BTRFS_UTIL_ERROR_START_SYNC_FAILED);
	PyModule_AddIntConstant(m, "ERROR_WAIT_SYNC_FAILED", BTRFS_UTIL_ERROR_WAIT_SYNC_FAILED);
	PyModule_AddIntConstant(m, "ERROR_GET_SUBVOL_INFO_FAILED", BTRFS_UTIL_ERROR_GET_SUBVOL_INFO_FAILED);
	PyModule_AddIntConstant(m, "ERROR_GET_SUBVOL_ROOTREF_FAILED", BTRFS_UTIL_ERROR_GET_SUBVOL_ROOTREF_FAILED);
	PyModule_AddIntConstant(m, "ERROR_INO_LOOKUP_USER_FAILED", BTRFS_UTIL_ERROR_INO_LOOKUP_USER_FAILED);
	PyModule_AddIntConstant(m, "ERROR_FS_INFO_FAILED", BTRFS_UTIL_ERROR_FS_INFO_FAILED);
}
