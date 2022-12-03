#pragma once

const size_t MAX_BODY_LENGTH = 1024;
const size_t MAX_HTTP_REQUEST_LENGTH = 1024;

const char *authURL = "/roap/api/auth";
const char *cmdURL = "/roap/api/command";
const char *httpTemplate = "POST %s HTTP/1.1\r\n"
	                   "Host: %s\r\n"
        	           "Connection: Keep-Alive\r\n"
                           "content-length: %i\r\n"
                  	   "content-type: application/atom+xml\r\n"
			   "user-agent: Manual C baby/0.0.1\r\n\r\n%s";

const char *reqKey = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			"<auth>\n"
			" <type>AuthKeyReq</type>\n"
			"</auth>";

const char *authKey = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                      "<auth>\n"
                      " <type>AuthReq</type>\n"
                      " <value>%s</value>\n"
                      "</auth>";

const char *handleKeyInput = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                             "<command>\n"
                             " <name>HandleKeyInput</name>\n"
                             " <value>%i</value>\n"
                             "</command>";

const char *handleTouchClick = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                             "<command>\n"
                             " <name>HandleTouchClick</name>\n"
                             "</command>";

const char *handleTouchMove = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                             "<command>\n"
                             " <name>HandleTouchMove</name>\n<value>"
                             " <x>%i</x>\n"
                             " <y>%i</y></value>\n"
                             "</command>";


int strncpy_s(char *dst, const char *src, const size_t n);

