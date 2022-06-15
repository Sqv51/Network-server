#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <QDebug>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}








void MainWindow::on_serverstart_clicked()
{
        //seçili protokolde server başlatır
        if(ui->comboBox->currentText() == "UDP")

        {
            ui->status->setText("UDP");
            ui->serverstart->setDisabled(1);
            qDebug("UDP");
            char buffer[50] = {0};
                struct sockaddr_in servaddr = {0};

                int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                if(sockfd == -1)
                {
                    qDebug("failed to create socket");
                    ui->serverstart->setDisabled(0);
                    ui->status->setText("Başarısız");
                }
                ui->status->setText("BAĞLANDI");
                servaddr.sin_family = AF_INET;
                servaddr.sin_port = htons(12345);
                servaddr.sin_addr.s_addr = INADDR_ANY;

                int rc = bind(sockfd, (const struct sockaddr *)&servaddr,
                    sizeof(servaddr));

                if(rc == -1)
                {
                    qDebug("failed to bind");
                    ::close(sockfd);
                    ui->status->setText("Başarısız");
                    ui->serverstart->setDisabled(0);
                }
                socklen_t len = 0;

                int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL,0, &len);
                buffer[n] = '\n';
                printf("%s", buffer);
                ui->textBrowser->setText(buffer);
                ::close(sockfd);

        }

        if(ui->comboBox->currentText() == "TCP")
        {
            int listening = socket(AF_INET, SOCK_STREAM, 0);
               if (listening == -1)
               {
                   cerr << "Can't create a socket! Quitting" << endl;
                   qDebug("soket oluşturulamadı");
               }

               // Bind the ip address and port to a socket
               sockaddr_in hint;
               hint.sin_family = AF_INET;
               hint.sin_port = htons(54000);
               inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

               bind(listening, (sockaddr*)&hint, sizeof(hint));

               // Tell Winsock the socket is for listening
               listen(listening, SOMAXCONN);

               // Wait for a connection
               sockaddr_in client;
               socklen_t clientSize = sizeof(client);

               int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

               char host[NI_MAXHOST];      // Client's remote name
               char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

               memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
               memset(service, 0, NI_MAXSERV);

               if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
               {
                   cout << host << " connected on port " << service << endl;
               }
               else
               {
                   inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
                   cout << host << " connected on port " << ntohs(client.sin_port) << endl;
               }

               // Close listening socket
               ::close(listening);

               // While loop: accept and echo message back to client
               char buf[4096];

               while (true)
               {
                   memset(buf, 0, 4096);

                   // Wait for client to send data
                   int bytesReceived = recv(clientSocket, buf, 4096, 0);
                   if (bytesReceived == -1)
                   {
                       cerr << "Error in recv(). Quitting" << endl;
                       break;
                   }

                   if (bytesReceived == 0)
                   {
                       cout << "Client disconnected " << endl;
                       break;
                   }

                   cout << string(buf, 0, bytesReceived) << endl;

                   // Echo message back to client
                   send(clientSocket, buf, bytesReceived + 1, 0);
               }

               // Close the socket
               ::close(clientSocket);


        }
        if(ui->comboBox->currentText() == "Websocket")
        {

        }



}

