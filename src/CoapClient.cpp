//
//  CoapClient.cpp
//  CoAP-simple-library
//
//  Created by POTADOS on 21/11/2018.
//  Copyright © 2018 POTADOS. All rights reserved.
//

#include "CoapClient.h"

CoapClient::CoapClient(UDP &udp) : Coap(udp) { }

bool CoapClient::registerCallback(callback c) {
    if (c) { responseCallback = c; }
    else { return false; }

    return true;
}

uint16_t CoapClient::get(IPAddress ip, int port, char *url) {
    return this->send(ip, port, url,
                      COAP_CON,     /* type */
                      COAP_GET,     /* method */
                      NULL,         /* token */
                      0,            /* token length */
                      NULL,         /* payload */
                      0);           /* payload length */
}

uint16_t CoapClient::put(IPAddress ip, int port, char *url, char *payload) {
    return this->send(ip, port, url,
                      COAP_CON,                     /* type */
                      COAP_PUT,                     /* method */
                      NULL,                         /* token */
                      0,                            /* token length */
                      (uint8_t *)payload,           /* payload */
                      (uint32_t)strlen(payload));   /* payload length */
}

uint16_t CoapClient::send(IPAddress ip, int port, char *url,
                    COAP_TYPE type,
                    COAP_METHOD method,
                    uint8_t *token,
                    uint8_t tokenlen,
                    uint8_t *payload,
                    uint32_t payloadlen) {

    CoapPacket packet(ip, url, type, method, token, tokenlen, payload, payloadlen);

    return this->sendPacket(packet, ip, port); /* returns message id */
}

bool CoapClient::launchCallback(CoapPacket &packet, IPAddress ip, int port) {
    if (responseCallback) { responseCallback(packet, ip, port); }
    else { return false; }

    return true;
 }

void CoapClient::packetRecievedBehavior(CoapPacket &request) {
    if (request.type == COAP_ACK || request.type == COAP_RESET) {
        launchCallback(request, udp->remoteIP(), udp->remotePort());
    }
}
