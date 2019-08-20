#include "can/threadcanreadmonitor.h"
#include <QByteArray>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <QDebug>

ThreadCANReadMonitor::ThreadCANReadMonitor(QObject *parent) :
    QThread(parent)
{
}

void ThreadCANReadMonitor::run()
{
    QByteArray baRecv;
    int sockfd;
    int nbytes;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

 //   char *ifname = "can0";

    if ((sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0){
        perror("Error while opening socket");
        return;
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(sockfd, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) <  0){
        perror("Error in socket bind");
        return;
    }
    while (1){
        memset(&frame, 0, sizeof(struct can_frame));
        nbytes = read(sockfd, &frame, sizeof(struct can_frame));
        printf("can recv from id %x: ", frame.can_id);
        if (nbytes > 0){
            baRecv.resize(frame.can_dlc);
            for (int i=0; i<frame.can_dlc; i++){
                printf("%3x", frame.data[i]);
                baRecv[i] = frame.data[i];
            }
            printf("\n");
            emit signalRecvMsg(baRecv, frame.can_id);
        }
    }
}
