#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sangesh");
MODULE_DESCRIPTION("TCP Flag Analyzer");
MODULE_VERSION("0.1");

/*
 * Module Initialization
 * Runs when the module is inserted using insmod.
 */
static unsigned int packet_hook(void *priv,
                                struct sk_buff *skb,
                                const struct nf_hook_state *state)
{
    struct iphdr *ip_header;

    /* Safety check */
    if (!skb)
        return NF_ACCEPT;

    /* Get the IPv4 header */
    ip_header = ip_hdr(skb);

    if (!ip_header)
        return NF_ACCEPT;

    printk(KERN_INFO "Source IP: %pI4\n", &ip_header->saddr);
    printk(KERN_INFO "Destination IP: %pI4\n", &ip_header->daddr);

    return NF_ACCEPT;
}
static struct nf_hook_ops nfho = {
    .hook = packet_hook,
    .hooknum = NF_INET_PRE_ROUTING,
    .pf = PF_INET,
    .priority = NF_IP_PRI_FIRST,
};

static int __init tcp_flag_init(void)
{
    int ret;

    printk(KERN_INFO "TCP Flag Analyzer Loaded\n");

    ret = nf_register_net_hook(&init_net, &nfho);

    if (ret) {
        printk(KERN_ERR "Failed to register Netfilter hook\n");
        return ret;
    }

    printk(KERN_INFO "Netfilter hook registered successfully\n");

    return 0;
}

/*
 * Module Cleanup
 * Runs when the module is removed using rmmod.
 */

static void __exit tcp_flag_exit(void)
{
    nf_unregister_net_hook(&init_net, &nfho);

    printk(KERN_INFO "TCP Flag Analyzer Unloaded\n");
}

module_init(tcp_flag_init);
module_exit(tcp_flag_exit);
