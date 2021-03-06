//
//  Coap.h
//  CoAP-simple-library
//
//  Created by POTADOS on 21/11/2018.
//  Copyright © 2018 POTADOS. All rights reserved.
//

/*
 CoAP library for Arduino.
 This software is released under the MIT License.
 Copyright (c) 2014 Hirotaka Niisato
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * 2019.1.27
 * Refine documents.
 
 * 2018.12.30
 * Improve the way of passing string from user callback to system.
 * Remove unnecessary codes in COAP_DELTA macro.
 * Fix comiler warnings.
 
 * 2018.11.23
 * Separate CoapServer and CoapClient.
 * Remove duplicated code.
 * Reorganize files and sources.
 * Add comments.
 
 * Song Byeong Jun, Potados
 * potados99@gmail.com
 */


#ifndef Coap_h
#define Coap_h

#include "CoapUri.h"

class Coap {
protected:
    /**
     * UDP communication.
     */
    UDP             *udp;
    
    /**
     * Store resources.
     */
    CoapUri         uri;
    
    /**
     * Flag: if this server started.
     */
    bool            started = false;
    
    /**
     * Send a packet to specific host.
     *
     * @param packet    Packet to send.
     * @param ip        Receiver IP.
     * @param port      Receiver port.
     *
     * @return          Message id of sent packet.
     */
    uint16_t       sendPacket(CoapPacket &packet, IPAddress ip, int port = COAP_DEFAULT_PORT);
    
    /**
     * Define a behavior when a complete packet arrives.
     *
     * @param request   incomming request packet.
     */
    virtual void    packetRecievedBehavior(CoapPacket &request) = 0;
    
public:
    /**
     * Initialize instance.
     *
     * @param udp       Udp instance to use.
     */
    Coap(UDP &udp);
    
    /**
     * Start udp communication.
     *
     * @param port      Port number of this server.
     */
    void            start(int port = COAP_DEFAULT_PORT);
    
    /**
     * Define repeated tasks.
     *
     * @return          False when packet is too big or not valid.
     */
    bool            loop();
};

#endif /* Coap_h */

