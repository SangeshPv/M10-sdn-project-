# M10-sdn-project-

=============================Overall Purpose=======================================
This kernel module attaches to the Netfilter PRE_ROUTING hook and inspects every incoming IPv4 TCP packet before the Linux kernel decides what to do with it.
It performs three levels of functionality:
Basic
Counts how many TCP packets contain each TCP flag.
Intermediate
Maintains counters representing different TCP connection states.
Advanced
Detects suspicious packets such as and drop:
SYN Flood attacks
SYN+FIN scans
NULL scans
XMAS scans


===================================Project for SDN TCP analyzer testing =================================================
How to enter the root folder
sudo su and password
then git clone
git clone https://github.com/sdnsangesh/tcp-flag-analyzer.git
cd tcp-flag-analyzer
or 
cd /root/projects/tcp-flag-analyzer
testing after entering the root folder
The Make file needs to be modified based on what you are testing basic,intermidiate,advanced rename this line
obj-m += tcp_flag_analyzer.o (the name of the file obj-m += tcp_flag_analyzer_basic.o) to run the right makefile 
make clean
make
sudo insmod tcp_flag_analyzer.ko
curl https://google.com
sudo rmmod tcp_flag_analyzer
dmesg | tail -50



=====================================OUTPUT FOR THE BASIC PROJECT========================================================

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



 ====================Output for the intermidiate part for TCP analyzer State connection================================== 


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


=======================OUTPUT FOR THE ADVANCED PROJECT WITHOUT DROPPING THE PACKETS======================================

root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# sudo insmod tcp_flag_analyzer.ko
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# seq 1 2000 | xargs -P20 -I{} curl -s https://youtube.com > /dev/null
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# rmmod tcp_flag_analyzer
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# dmesg | tail -50
[ 1183.607206] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 1183.607238] TCP Packet
[ 1183.607268] Source IP: 172.217.23.78
[ 1183.607311] Destination IP: 192.168.64.10
[ 1183.607356] Ports: 443 -> 55032
[ 1183.607414] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 1183.607448] TCP Packet
[ 1183.607479] Source IP: 172.217.23.78
[ 1183.607529] Destination IP: 192.168.64.10
[ 1183.607587] Ports: 443 -> 55032
[ 1183.607628] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 1183.607657] TCP Packet
[ 1183.607685] Source IP: 172.217.23.78
[ 1183.607712] Destination IP: 192.168.64.10
[ 1183.607752] Ports: 443 -> 55032
[ 1183.607779] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=1 URG=0
[ 1183.625549] TCP Packet
[ 1183.625651] Source IP: 172.217.23.78
[ 1183.625683] Destination IP: 192.168.64.10
[ 1183.625710] Ports: 443 -> 55032
[ 1183.625738] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[ 1183.625766] TCP Packet
[ 1183.625792] Source IP: 172.217.23.78
[ 1183.625819] Destination IP: 192.168.64.10
[ 1183.625859] Ports: 443 -> 55032
[ 1183.625891] Flags: SYN=0 ACK=1 FIN=1 RST=0 PSH=0 URG=0
[ 1183.626937] TCP Packet
[ 1183.626998] Source IP: 172.217.23.78
[ 1183.627031] Destination IP: 192.168.64.10
[ 1183.627062] Ports: 443 -> 55032
[ 1183.627093] Flags: SYN=0 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[ 1257.188973] ===== TCP Flag Statistics =====
[ 1257.188985] SYN : 1984
[ 1257.188988] ACK : 30776
[ 1257.188991] FIN : 1881
[ 1257.188994] RST : 2
[ 1257.188997] PSH : 17838
[ 1257.189000] URG : 0
[ 1257.189003] ===== TCP Connection State Statistics =====
[ 1257.189006] STATE_SYN : 0
[ 1257.189009] STATE_SYN_ACK : 1984
[ 1257.189012] STATE_ACK : 9072
[ 1257.189015] STATE_FIN : 1881
[ 1257.189017] STATE_RST : 2
[ 1257.189020] STATE_ESTABLISHED : 17838
[ 1257.189023] SYN+FIN Detected : 0
[ 1257.189026] NULL Scan Detected : 0
[ 1257.189030] XMAS Scan Detected : 0
[ 1257.189033] SYN Flood Detected : 1885
[ 1257.189036] TCP Flag Analyzer Unloaded
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# 

============================OUTPUT FOR THE ADVANCED PROJECT WITH DROPPING THE PACKETS===================================

root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# sudo insmod tcp_flag_analyzer.ko
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# seq 1 2000 | xargs -P20 -I{} curl -s https://youtube.com > /dev/null
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# rmmod tcp_flag_analyzer
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# dmesg | tail -50
[  613.056152] ALERT: Possible SYN Flood detected!
[  613.089903] TCP Packet
[  613.089975] Source IP: 185.125.190.100
[  613.090010] Destination IP: 192.168.64.10
[  613.090042] Ports: 80 -> 38996
[  613.090074] Flags: SYN=1 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[  613.090106] ALERT: Possible SYN Flood detected!
[  613.319921] TCP Packet
[  613.320002] Source IP: 91.189.91.97
[  613.320038] Destination IP: 192.168.64.10
[  613.320070] Ports: 80 -> 43706
[  613.320103] Flags: SYN=1 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[  613.320135] ALERT: Possible SYN Flood detected!
[  613.350025] TCP Packet
[  613.350091] Source IP: 91.189.91.97
[  613.350124] Destination IP: 192.168.64.10
[  613.350157] Ports: 80 -> 43706
[  613.350189] Flags: SYN=1 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[  613.350248] ALERT: Possible SYN Flood detected!
[  625.399948] TCP Packet
[  625.399963] Source IP: 185.125.190.101
[  625.399972] Destination IP: 192.168.64.10
[  625.399974] Ports: 80 -> 56318
[  625.399976] Flags: SYN=1 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[  625.399982] ALERT: Possible SYN Flood detected!
[  625.677328] TCP Packet
[  625.677399] Source IP: 185.125.190.100
[  625.677417] Destination IP: 192.168.64.10
[  625.677430] Ports: 80 -> 55746
[  625.677448] Flags: SYN=1 ACK=1 FIN=0 RST=0 PSH=0 URG=0
[  625.677463] ALERT: Possible SYN Flood detected!
[  625.812730] ===== TCP Flag Statistics =====
[  625.812742] SYN : 2229
[  625.812746] ACK : 1287
[  625.812749] FIN : 80
[  625.812752] RST : 6
[  625.812755] PSH : 640
[  625.812763] URG : 0
[  625.812765] ===== TCP Connection State Statistics =====
[  625.812769] STATE_SYN : 0
[  625.812772] STATE_SYN_ACK : 99
[  625.812775] STATE_ACK : 468
[  625.812778] STATE_FIN : 80
[  625.812781] STATE_RST : 6
[  625.812783] STATE_ESTABLISHED : 640
[  625.812786] SYN+FIN Detected : 0
[  625.812789] NULL Scan Detected : 0
[  625.812793] XMAS Scan Detected : 0
[  625.812796] SYN Flood Detected : 2130
[  625.812799] TCP Flag Analyzer Unloaded
root@sdnsangesh-Apple-Virtualization-Generic-Platform:~/projects/tcp-flag-analyzer# 

AS we can see the STATE_SYN_ACK : 99 as from the 100th packet is dropped

==========================================================================================================================




