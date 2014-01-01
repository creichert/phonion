#!/usr/bin/env python

import tc_client

listen_socket = tc_client.tryBindPort("127.0.0.1", 9050)
self.buddy_list = tc_client.BuddyList(self.callbackMessage, socket)

def callbackMessage(self, callback_type, callback_data):
    print "CALLBACK TYPE: " + str(callback_type)
    print "CALLBACK DATA: " + str(callback_data)

