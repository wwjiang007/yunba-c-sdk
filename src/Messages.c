/*******************************************************************************
 * Copyright (c) 2009, 2013 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *******************************************************************************/

/**
 * @file
 * \brief Trace messages
 *
 */


#include "Messages.h"
#include "Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "Heap.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define max_msg_len 120

static char* protocol_message_list[] =
{
	"%d %s -> CONNECT cleansession: %d (%d)", /* 0, was 131, 68 and 69 */
	"%d %s <- CONNACK rc: %d", /* 1, was 132 */
	"%d %s -> CONNACK rc: %d (%d)", /* 2, was 138 */
	"%d %s <- PINGREQ", /* 3, was 35 */
	"%d %s -> PINGRESP (%d)", /* 4 */
	"%d %s <- DISCONNECT", /* 5 */
	"%d %s <- SUBSCRIBE msgid: %llu", /* 6, was 39 */
	"%d %s -> SUBACK msgid: %llu (%d)", /* 7, was 40 */
	"%d %s <- UNSUBSCRIBE msgid: %llu", /* 8, was 41 */
	"%d %s -> UNSUBACK msgid: %llu (%d)", /* 9 */
	"%d %s -> PUBLISH msgid: %llu qos: %d retained: %d (%d) payload: %.*s", /* 10, was 42 */
	"%d %s <- PUBLISH msgid: %llu qos: %d retained: %d payload: %.*s", /* 11, was 46 */
	"%d %s -> PUBACK msgid: %llu (%d)", /* 12, was 47 */
	"%d %s -> PUBREC msgid: %llu (%d)", /* 13, was 48 */
	"%d %s <- PUBACK msgid: %llu", /* 14, was 49 */
	"%d %s <- PUBREC msgid: %llu", /* 15, was 53 */
	"%d %s -> PUBREL msgid: %llu (%d)", /* 16, was 57 */
	"%d %s <- PUBREL msgid: %llu", /* 17, was 58 */
	"%d %s -> PUBCOMP msgid: %llu (%d)", /* 18, was 62 */
	"%d %s <- PUBCOMP msgid: %llu", /* 19, was 63 */
	"%d %s -> PINGREQ (%d)", /* 20, was 137 */
	"%d %s <- PINGRESP", /* 21, was 70 */
	"%d %s -> SUBSCRIBE msgid: %llu (%d)", /* 22, was 72 */
	"%d %s <- SUBACK msgid: %llu", /* 23, was 73 */
	"%d %s <- UNSUBACK msgid: %llu", /* 24, was 74 */
	"%d %s -> UNSUBSCRIBE msgid: %llu (%d)", /* 25, was 106 */
	"%d %s <- CONNECT", /* 26 */
	"%d %s -> PUBLISH qos: 0 retained: %d (%d)", /* 27 */
	"%d %s -> DISCONNECT (%d)", /* 28 */
};

static char* trace_message_list[] =
{
	"Failed to remove client from bstate->clients", /* 0 */
	"Removed client %s from bstate->clients, socket %d", /* 1 */
	"Packet_Factory: unhandled packet type %d", /* 2 */
	"Packet %s received from client %s for message identifier %d, but no record of that message identifier found", /* 3 */
	"Packet %s received from client %s for message identifier %d, but message is wrong QoS, %d", /* 4 */
	"Packet %s received from client %s for message identifier %d, but message is in wrong state", /* 5 */
	"%s received from client %s for message id %d - removing publication", /* 6 */
	"Trying %s again for client %s, socket %d, message identifier %d", /* 7 */
	"Socket error for client identifier %s, socket %d, peer address %s; ending connection", /* 8 */
	"(%lu) %*s(%d)> %s:%d", /* 9 */
	"(%lu) %*s(%d)< %s:%d", /* 10 */
	"(%lu) %*s(%d)< %s:%d (%d)", /* 11 */
	"Storing unsent QoS 0 message", /* 12 */
};

/**
 * Get a log message by its index
 * @param index the integer index
 * @param log_level the log level, used to determine which message list to use
 * @return the message format string
 */
char* Messages_get(int index, int log_level)
{
	char* msg = NULL;

	if (log_level == TRACE_PROTOCOL)
		msg = (index >= 0 && index < ARRAY_SIZE(protocol_message_list)) ? protocol_message_list[index] : NULL;
	else
		msg = (index >= 0 && index < ARRAY_SIZE(trace_message_list)) ? trace_message_list[index] : NULL;
	return msg;
}

