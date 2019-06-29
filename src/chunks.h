
#ifndef CHUNKS_H_
	#define CHUNKS_H_

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <assert.h>
	#include <time.h>

	#include <libxml/parser.h>
	#include <libxml/tree.h>

	#include <curl/curl.h>

	#define URL "http://192.168.1.1/api/sms/send-sms"

	size_t read_callback(char *buffer, size_t size, size_t nitems, void *userdata);
	size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
	xmlDocPtr create_request(char* content, char* phone);
	xmlChar* get_xml_node_content(xmlNode* node, char* param);

#endif /* CHUNKS_H_ */
