/*
 *  IP Messenger Grwoling part 
 *
 *  Copyright (c) 2009 snaka<snaka.gml@gmail.com>
 */

#include <stdio.h>
#include <winsock2.h>

void GNTP_SendAndRecieve(char *message) {
  struct sockaddr_in server;
  SOCKET  sock;
  char buf[2048];
 
  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  // Configure socket
  server.sin_family = AF_INET;
  server.sin_port = htons(23053);
  server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
 
  // Connect to server
  connect(sock, (struct sockaddr *)&server, sizeof(server));
 
  // Send data (Register)
  memset(buf, 0, sizeof(buf));
  _snprintf(buf, sizeof(buf), message);
  send(sock, buf, sizeof(buf), 0);
  
  // Recieve data from server
  memset(buf, 0, sizeof(buf));
  int n = recv(sock, buf, sizeof(buf), 0);
  
  closesocket(sock);
}
