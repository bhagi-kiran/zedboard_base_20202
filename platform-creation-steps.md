## Step by Step Guide to create Vitis Platform

>The board for which we are creating platform is Zedboard

***Creating a Vitis Platform includes three main steps***
>- **1. Hardware: Using Vivado to prepare underlying hardware components and generate .XSA file***
>- **2. Software: Using PetaLinux to configure and generate the corresponding linux OS**
>- **3. Platform: Using Vitis to integrate Hardware and Software Components and generate final platform**

***Required Softwares***
>- **Xilinx Unified Software**
>- **PetaLinux**
>- *Note: The version of these two software must be same*

# 1. Hardware
**The first thing we are going to do is create the directory structure. For this, we need a directory named zedboard, under this create directories called hardware.**

```bash
mkdir -p ~/workspace/zedboard
cd workspace/zedboard
mkdir hardware
cd hardware/
```
Under the hardware directory, create a new Vivado project targeting the Zedboard.
![image](https://user-images.githubusercontent.com/115934581/219945042-d31f8d84-fe6c-4224-9d8c-928ab7063e46.png)
![image](https://user-images.githubusercontent.com/115934581/219945124-f772b98d-a60c-44e4-b347-dbd2b26ce80e.png)
![image](https://user-images.githubusercontent.com/115934581/219945332-581b01b9-5c58-4f91-b500-20f476b87260.png)
![image](https://user-images.githubusercontent.com/115934581/219945573-53df4ef7-3767-45f8-adc2-348ccc6319c7.png)
![image](https://user-images.githubusercontent.com/115934581/219945731-821ed09d-3a2b-4051-8e77-d4462e4c8525.png)
![image](https://user-images.githubusercontent.com/115934581/219946134-62fa4c6e-9d8d-4850-80f9-fa4e1237deaa.png)
![image](https://user-images.githubusercontent.com/115934581/219946370-b859f60b-2d15-4dae-825d-28e99225b14f.png)
![image](https://user-images.githubusercontent.com/115934581/219946832-d1bc9ba7-2b6d-4aae-90a8-b01afbf360b1.png)
![image](https://user-images.githubusercontent.com/115934581/219946911-2deb630f-1e60-43ff-958b-b47f8a34d5fc.png)
![image](https://user-images.githubusercontent.com/115934581/219947245-30fdcc24-dad9-459c-b468-ba3f215d1ed1.png)
![image](https://user-images.githubusercontent.com/115934581/219947704-032f3b69-500c-4b43-91ca-f6f908ac7555.png)
![image](https://user-images.githubusercontent.com/115934581/219947881-4f0e8175-eebb-40bc-8727-b5c94076e169.png)
![image](https://user-images.githubusercontent.com/115934581/219948039-fb773f96-3bc1-4c02-a0cc-334e0d4fc0e5.png)
![image](https://user-images.githubusercontent.com/115934581/219948122-344f6748-c847-4bcb-9d05-074274da7562.png)
![image](https://user-images.githubusercontent.com/115934581/219948308-31f7974b-5216-40a9-9727-3fa4980d8009.png)
![image](https://user-images.githubusercontent.com/115934581/219948471-5db8fa8f-7811-44af-a206-9caba2eb91e9.png)
![image](https://user-images.githubusercontent.com/115934581/219948557-f965dcd4-29ca-46d8-9411-c7ca887f8174.png)
![image](https://user-images.githubusercontent.com/115934581/219948655-c592ac93-c6f7-45d2-9eb0-e33a02b7c8cd.png)
![image](https://user-images.githubusercontent.com/115934581/219950443-3dc6771a-8f5c-4a5c-b557-7774d1523fba.png)
![image](https://user-images.githubusercontent.com/115934581/219950613-55ee5f96-4414-4bc7-b782-422825c23792.png)
![image](https://user-images.githubusercontent.com/115934581/219950868-f1cc4a4c-1802-4f5a-9133-26f125f93ead.png)
<!-- PENDING IMGS -->
![image](https://user-images.githubusercontent.com/115934581/219954083-edd9c7b6-15b5-4d23-b495-808310e3429b.png)
![image](https://user-images.githubusercontent.com/115934581/219954194-544c141a-1480-415b-b47a-4f96a487afa2.png)
![image](https://user-images.githubusercontent.com/115934581/219954258-870fd4cb-5bef-4060-9f4a-3245affdb25e.png)
![image](https://user-images.githubusercontent.com/115934581/219954409-2933cc06-d5a6-4719-bb34-06b89f9c3aea.png)
![image](https://user-images.githubusercontent.com/115934581/219954464-1d415bf5-f6ce-463c-9041-c6e8144cef4d.png)
![image](https://user-images.githubusercontent.com/115934581/219954510-4943c91a-3fa6-492c-bd78-dcdce3372f61.png)

# 2. Software
Navigate to zedboard directory
```bash
mkdir software
cd software
mkdir linux_files
cd linux_files
mkdir boot image
cd ..
source /tools/Xilinx/PetaLinux/2020.2/settings.sh
petalinux-create -t project --template zynq -n zedboard_base_20202-petalinux
#command to create petalinux project
cd zedboard_base_20202-petalinux
petalinux-config --get-hw-description=../../hardware/zedboard_base_20202-vivado
#command           option             path containing the xsa file
petalinux-config -c kernel
#after the command linux-xlnx configuration window will open
```
![image](https://user-images.githubusercontent.com/115934581/223687854-b219ab35-7ec0-43b6-8843-af0c79b65e63.png)
![image](https://user-images.githubusercontent.com/115934581/223688215-a4132e43-7a4d-48c9-a829-c177bf33fdae.png)
![image](https://user-images.githubusercontent.com/115934581/223688285-9d65e1b4-fa15-4ec7-8efd-517501d76522.png)
![image](https://user-images.githubusercontent.com/115934581/223688342-e232edf2-ccd3-46dc-8fe8-cb5d9bb05166.png)

```bash
gedit ./project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi
#add these lines
/include/ "system-conf.dtsi"
/ {
};

&amba {
	zyxclmm_drm {
		compatible = "xlnx,zocl";
		status = "okay";

	};
};
gedit ./project-spec/meta-user/conf/user-rootfsconfig
#add these

#Note: Mention Each package in individual line
#These packages will get added into rootfs menu entry

CONFIG_gpio-demo
CONFIG_peekpoke
CONFIG_xrt
CONFIG_xrt-dev
CONFIG_zocl
CONFIG_opencl-clhpp-dev
CONFIG_opencl-headers-dev
CONFIG_packagegroup-petalinux-opencv

petalinux-config -c rootfs
#configuration window will appear
```
![image](https://user-images.githubusercontent.com/115934581/223690349-2a11c304-5279-4a1b-b4bf-905232390868.png)
![image](https://user-images.githubusercontent.com/115934581/223690506-e4fa2ad0-7a19-40a0-896f-4fe1f00845b0.png)

```bash
#Now we should build embedded linux by this command
petalinux-build
cd ~/workspace/zedboard/software/zedboard_base_20202-petalinux/images/linux
petalinux-package --boot --format BIN --fsbl zynq_fsbl.elf --u-boot u-boot.elf --fpga system.bit --force
petalinux-build --sdk
./sdk.sh
#it will ask for a directory
#enter path to linux_files
cd ~/workspace/zedboard/software/linux_files/boot
gedit linux.bif
#add these
/* linux */
the_ROM_image:
{
   [bootloader] <fsbl.elf>
   <bitstream>
   <u-boot.elf>
}
gedit qemu_args.txt
#add these
-M
arm-generic-fdt-7series
-serial
/dev/null
-serial
mon:stdio
-device
loader,addr=0xf8000008,data=0xDF0D,data-len=4
-device
loader,addr=0xf8000140,data=0x00500801,data-len=4
-device
loader,addr=0xf800012c,data=0x1ed044d,data-len=4
-device
loader,addr=0xf8000108,data=0x0001e008,data-len=4
-device
loader,addr=0xF800025C,data=0x00000005,data-len=4
-device
loader,addr=0xF8000240,data=0x00000000,data-len=4
-boot
mode=5
-kernel
<zedboard_base_20202/qemu/u-boot.elf>
-machine
linux=on

cd ~/workspace/zedboard/software/zedboard_base_20202-petalinux/images/linux
cp u-boot.elf <path-to>/boot
cp zynq_fsbl.elf <path-to>/boot/fsbl.elf
cp boot.scr image.ub rootfs.cpio <path-to>/image
```
# 3. Platform

Navigate to zedboard directory

```bash
mkdir platform
cd platform
vitis &
#command to run vitis software
#need to source settings64.sh from vitis 
```
![image](https://user-images.githubusercontent.com/115934581/223696590-6c9cab55-f7a1-4dff-9272-412aed823f77.png)
![image](https://user-images.githubusercontent.com/115934581/223697650-4139d4c7-7b1a-48e9-a361-c894cee795cd.png)
![image](https://user-images.githubusercontent.com/115934581/223698006-3f9fb752-2af7-41db-8198-237a1f0df6e2.png)

**Navigate to the paths of the respective files and build the project**

![image](https://user-images.githubusercontent.com/115934581/223698965-f6a63888-35f9-4baa-94ca-243decd70027.png)


# Hence, platform creation was successful

