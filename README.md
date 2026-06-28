# M10-sdn-project-
Project for SDN TCP analyzer
OUTPUT FOR THE BASIC PROJECT
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# insmod tcp_flag_analyzer.ko
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# for i in {1..10}
do
    curl -s https://google.com > /dev/null
done
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# rmmod tcp_flag_analyzer
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# dmesg | tail -50
[ 8418.373784] Ports: 443 -> 41638
[ 8418.373810] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 8418.391488] TCP Packet
[ 8418.391548] Source IP: 192.178.194.100
[ 8418.391584] Destination IP: 192.168.64.10
[ 8418.391611] Ports: 443 -> 41638
[ 8418.391638] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[ 8418.500968] TCP Packet
[ 8418.501039] Source IP: 192.178.194.100
[ 8418.501067] Destination IP: 192.168.64.10
[ 8418.501094] Ports: 443 -> 41638
[ 8418.501121] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 8418.501147] TCP Packet
[ 8418.501173] Source IP: 192.178.194.100
[ 8418.501199] Destination IP: 192.168.64.10
[ 8418.501237] Ports: 443 -> 41638
[ 8418.501264] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 8418.501291] TCP Packet
[ 8418.501318] Source IP: 192.178.194.100
[ 8418.501345] Destination IP: 192.168.64.10
[ 8418.501373] Ports: 443 -> 41638
[ 8418.501408] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 8418.519151] TCP Packet
[ 8418.519182] Source IP: 192.178.194.100
[ 8418.519195] Destination IP: 192.168.64.10
[ 8418.519206] Ports: 443 -> 41638
[ 8418.519217] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[ 8418.519249] TCP Packet
[ 8418.519262] Source IP: 192.178.194.100
[ 8418.519274] Destination IP: 192.168.64.10
[ 8418.519287] Ports: 443 -> 41638
[ 8418.519299] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[ 8418.519319] TCP Packet
[ 8418.519339] Source IP: 192.178.194.100
[ 8418.519351] Destination IP: 192.168.64.10
[ 8418.519363] Ports: 443 -> 41638
[ 8418.519380] Flags: SYN=0 ACK=1 FIN=1 RST=0 PSH=0 URG=0
[ 8418.520128] TCP Packet
[ 8418.520131] Source IP: 192.178.194.100
[ 8418.520134] Destination IP: 192.168.64.10
[ 8418.520140] Ports: 443 -> 41638
[ 8418.520143] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[ 8436.183632] ===== TCP Flag Statistics =====
[ 8436.183638] SYN : 12
[ 8436.183640] ACK : 163
[ 8436.183642] FIN : 12
[ 8436.183644] RST : 5
[ 8436.183646] PSH : 87
[ 8436.183647] URG : 0
[ 8436.183649] TCP Flag Analyzer Unloaded
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer#



Output for the intermidiate part for TCP analyzer State connection 
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# insmod tcp_flag_analyzer.ko
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# for i in {1..10}; do     curl -s https://google.com > /dev/null; done
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# rmmod tcp_flag_analyzer
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# dmesg | tail -50
[10493.494449] TCP Packet
[10493.494546] Source IP: 142.251.27.102
[10493.494585] Destination IP: 192.168.64.10
[10493.494618] Ports: 443 -> 34914
[10493.494651] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[10493.494683] TCP Packet
[10493.494746] Source IP: 142.251.27.102
[10493.494774] Destination IP: 192.168.64.10
[10493.494800] Ports: 443 -> 34914
[10493.494838] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[10493.494865] TCP Packet
[10493.494915] Source IP: 142.251.27.102
[10493.494943] Destination IP: 192.168.64.10
[10493.494969] Ports: 443 -> 34914
[10493.495008] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[10493.510762] TCP Packet
[10493.510774] Source IP: 142.251.27.102
[10493.510780] Destination IP: 192.168.64.10
[10493.510783] Ports: 443 -> 34914
[10493.510787] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[10493.510792] TCP Packet
[10493.510794] Source IP: 142.251.27.102
[10493.510797] Destination IP: 192.168.64.10
[10493.510806] Ports: 443 -> 34914
[10493.510809] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[10493.510812] TCP Packet
[10493.510815] Source IP: 142.251.27.102
[10493.510817] Destination IP: 192.168.64.10
[10493.510819] Ports: 443 -> 34914
[10493.510822] Flags: SYN=0 ACK=1 FIN=1 RST=0 PSH=0 URG=0
[10493.512424] TCP Packet
[10493.512431] Source IP: 142.251.27.102
[10493.512439] Destination IP: 192.168.64.10
[10493.512441] Ports: 443 -> 34914
[10493.512444] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[10520.804217] ===== TCP Flag Statistics =====
[10520.804228] SYN : 10
[10520.804232] ACK : 161
[10520.804235] FIN : 10
[10520.804238] RST : 0
[10520.804241] PSH : 87
[10520.804244] URG : 0
[10520.804247] ===== TCP Connection State Statistics =====
[10520.804250] STATE_SYN : 0
[10520.804253] STATE_SYN_ACK : 10
[10520.804255] STATE_ACK : 54
[10520.804258] STATE_FIN : 10
[10520.804261] STATE_RST : 0
[10520.804264] STATE_ESTABLISHED : 87
[10520.804267] TCP Flag Analyzer Unloaded
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# 



