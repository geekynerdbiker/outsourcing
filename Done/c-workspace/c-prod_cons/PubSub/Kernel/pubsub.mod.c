#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xdd8f8694, "module_layout" },
	{ 0x445df0ed, "netlink_kernel_release" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x9a50d23, "__netlink_kernel_create" },
	{ 0xaaa930a7, "init_net" },
	{ 0xb5f94cce, "netlink_unicast" },
	{ 0xcf02ccb1, "__nlmsg_put" },
	{ 0x580fdcdf, "__alloc_skb" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7251EEAB12D5358DD3B988F");
