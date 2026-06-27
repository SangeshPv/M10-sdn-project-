#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/atomic.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sangesh");
MODULE_DESCRIPTION("TCP Flag Analyzer");
MODULE_VERSION("0.1");
enum tcp_flag_index {
    TCP_FIN = 0,
    TCP_SYN,
    TCP_RST,
    TCP_PSH,
    TCP_ACK,
    TCP_URG,
    TCP_FLAG_COUNT
};

static atomic_t flag_counter[TCP_FLAG_COUNT];

/*
 * Netfilter Hook Function
 * Called whenever a TCP packet reaches PRE_ROUTING.
 */
static unsigned int packet_hook(void *priv,
                                struct sk_buff *skb,
                                const struct nf_hook_state *state)
{
    struct iphdr *ip_header;
    struct tcphdr *tcp_header;

    /* Safety check */
if (!skb)
    return NF_ACCEPT;

ip_header = ip_hdr(skb);

if (!ip_header)
    return NF_ACCEPT;

/* Only process TCP packets */
if (ip_header->protocol != IPPROTO_TCP)
    return NF_ACCEPT;

/* Get TCP header */
tcp_header = tcp_hdr(skb);

if (!tcp_header)
    return NF_ACCEPT;
   /* Print packet information */
printk(KERN_INFO "TCP Packet\n");
printk(KERN_INFO "Source IP: %pI4\n", &ip_header->saddr);
printk(KERN_INFO "Destination IP: %pI4\n", &ip_header->daddr);

printk(KERN_INFO
       "Ports: %u -> %u\n",
       ntohs(tcp_header->source),
       ntohs(tcp_header->dest));

printk(KERN_INFO
       "Flags: SYN=%d ACK=%d FIN=%d RST=%d PSH=%d URG=%d\n",
       tcp_header->syn,
       tcp_header->ack,
       tcp_header->fin,
       tcp_header->rst,
       tcp_header->psh,
       tcp_header->urg);

       if (tcp_header->syn)
    atomic_inc(&flag_counter[TCP_SYN]);

if (tcp_header->ack)
    atomic_inc(&flag_counter[TCP_ACK]);

if (tcp_header->fin)
    atomic_inc(&flag_counter[TCP_FIN]);

if (tcp_header->rst)
    atomic_inc(&flag_counter[TCP_RST]);

if (tcp_header->psh)
    atomic_inc(&flag_counter[TCP_PSH]);

if (tcp_header->urg)
    atomic_inc(&flag_counter[TCP_URG]);
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
    int i;

    printk(KERN_INFO "TCP Flag Analyzer Loaded\n");

    for (i = 0; i < TCP_FLAG_COUNT; i++)
        atomic_set(&flag_counter[i], 0);

    ret = nf_register_net_hook(&init_net, &nfho);

    if (ret) {
        printk(KERN_ERR "Failed to register Netfilter hook\n");
        return ret;
    }

    printk(KERN_INFO "Netfilter hook registered successfully\n");

    return 0;
}

/*
 * Netfilter Hook Function
 * Called whenever an IPv4 packet reaches the PRE_ROUTING hook.
 */

static void __exit tcp_flag_exit(void)
{
    /* First unregister the Netfilter hook */
    nf_unregister_net_hook(&init_net, &nfho);

    /* Print the final statistics */
    printk(KERN_INFO "===== TCP Flag Statistics =====\n");
    printk(KERN_INFO "SYN : %d\n", atomic_read(&flag_counter[TCP_SYN]));
    printk(KERN_INFO "ACK : %d\n", atomic_read(&flag_counter[TCP_ACK]));
    printk(KERN_INFO "FIN : %d\n", atomic_read(&flag_counter[TCP_FIN]));
    printk(KERN_INFO "RST : %d\n", atomic_read(&flag_counter[TCP_RST]));
    printk(KERN_INFO "PSH : %d\n", atomic_read(&flag_counter[TCP_PSH]));
    printk(KERN_INFO "URG : %d\n", atomic_read(&flag_counter[TCP_URG]));

    /* Module unloaded message */
    printk(KERN_INFO "TCP Flag Analyzer Unloaded\n");
}

module_init(tcp_flag_init);
module_exit(tcp_flag_exit);
