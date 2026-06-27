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
/*This intermediate project to monitor the state of the TCP connection */
enum tcp_conn_state {
    STATE_SYN = 0,
    STATE_SYN_ACK,
    STATE_ACK,
    STATE_FIN,
    STATE_RST,
    STATE_ESTABLISHED,
    STATE_COUNT
};
static atomic_t flag_counter[TCP_FLAG_COUNT];
static atomic_t state_counter[STATE_COUNT];
static atomic_t null_scan_counter;

/* advanced project
* to check syn+fin stealth detection and syn flood detection
*/
static atomic_t syn_fin_counter;


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

    /* Connection state counters */

if (tcp_header->syn && !tcp_header->ack)
    atomic_inc(&state_counter[STATE_SYN]);

if (tcp_header->syn && tcp_header->ack)
    atomic_inc(&state_counter[STATE_SYN_ACK]);

if (!tcp_header->syn &&
    tcp_header->ack &&
    !tcp_header->psh &&
    !tcp_header->fin)
    atomic_inc(&state_counter[STATE_ACK]);

if (tcp_header->fin)
    atomic_inc(&state_counter[STATE_FIN]);

if (tcp_header->rst)
    atomic_inc(&state_counter[STATE_RST]);

if (tcp_header->psh && tcp_header->ack)
    atomic_inc(&state_counter[STATE_ESTABLISHED]);    
/* Detect SYN + FIN packets */

if (tcp_header->syn && tcp_header->fin)
{
    atomic_inc(&syn_fin_counter);

    printk(KERN_WARNING
           "ALERT: SYN+FIN packet detected!\n");

    printk(KERN_WARNING
           "Source: %pI4:%u\n",
           &ip_header->saddr,
           ntohs(tcp_header->source));

    printk(KERN_WARNING
           "Destination: %pI4:%u\n",
           &ip_header->daddr,
           ntohs(tcp_header->dest));
}    
if (!tcp_header->syn &&
    !tcp_header->ack &&
    !tcp_header->fin &&
    !tcp_header->rst &&
    !tcp_header->psh &&
    !tcp_header->urg)
{
    atomic_inc(&null_scan_counter);

    printk(KERN_WARNING
           "ALERT: NULL scan detected!\n");

    printk(KERN_WARNING
           "Source: %pI4:%u\n",
           &ip_header->saddr,
           ntohs(tcp_header->source));

    printk(KERN_WARNING
           "Destination: %pI4:%u\n",
           &ip_header->daddr,
           ntohs(tcp_header->dest));
}
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
     for (i = 0; i < STATE_COUNT; i++)
        atomic_set(&state_counter[i], 0);

    atomic_set(&syn_fin_counter, 0);   
    atomic_set(&null_scan_counter, 0);

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

    printk(KERN_INFO "===== TCP Connection State Statistics =====\n");
    printk(KERN_INFO "STATE_SYN : %d\n", atomic_read(&state_counter[STATE_SYN]));
    printk(KERN_INFO "STATE_SYN_ACK : %d\n", atomic_read(&state_counter[STATE_SYN_ACK]));
    printk(KERN_INFO "STATE_ACK : %d\n", atomic_read(&state_counter[STATE_ACK]));
    printk(KERN_INFO "STATE_FIN : %d\n", atomic_read(&state_counter[STATE_FIN]));
    printk(KERN_INFO "STATE_RST : %d\n", atomic_read(&state_counter[STATE_RST]));
    printk(KERN_INFO "STATE_ESTABLISHED : %d\n", atomic_read(&state_counter[STATE_ESTABLISHED]));
    printk(KERN_INFO "SYN+FIN Detected : %d\n", atomic_read(&syn_fin_counter));
    printk(KERN_INFO "NULL Scan Detected : %d\n", atomic_read(&null_scan_counter));

    /* Module unloaded message */
    printk(KERN_INFO "TCP Flag Analyzer Unloaded\n");
}

module_init(tcp_flag_init);
module_exit(tcp_flag_exit);
