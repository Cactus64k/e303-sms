#include "chunks.h"

xmlDocPtr create_request(char* content, char* phone)
{
	assert(phone != NULL);

	char buff[32];
	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");

	xmlNode* root_node = xmlNewNode(NULL,BAD_CAST"request");
	xmlDocSetRootElement(doc, root_node);

	xmlNodePtr index_node		= xmlAddChild(root_node, xmlNewNode(NULL,BAD_CAST"Index"));
	xmlNodeAddContent(index_node, BAD_CAST"-1");

	xmlNodePtr phones_node		= xmlAddChild(root_node, xmlNewNode(NULL,BAD_CAST"Phones"));
	xmlNodePtr phone_node		= xmlAddChild(phones_node, xmlNewNode(NULL,BAD_CAST"Phone"));
	xmlNodeAddContent(phone_node, BAD_CAST(phone));

	xmlAddChild(root_node, xmlNewNode(NULL,BAD_CAST"Sca"));

	xmlNodePtr content_node		= xmlAddChild(root_node, xmlNewNode(NULL,BAD_CAST"Content"));
	if(content != NULL)
		xmlNodeAddContent(content_node, BAD_CAST(content));

	xmlNodePtr lenth_node		= xmlAddChild(root_node, xmlNewNode(NULL,BAD_CAST"Length"));
	snprintf(buff, sizeof(buff)-1, "%zu", strlen(content));
	xmlNodeAddContent(lenth_node, BAD_CAST(buff));

	xmlNodePtr reserved_node	= xmlAddChild(root_node, xmlNewNode(NULL,BAD_CAST"Reserved"));
	xmlNodeAddContent(reserved_node, BAD_CAST"1");

	xmlNodePtr date_node		= xmlAddChild(root_node, xmlNewNode(NULL,BAD_CAST"Date"));
	time_t t = time(0);
	struct tm* tt = localtime(&t);
	strftime(buff, sizeof(buff)-1, "%Y-%m-%d %X", tt);
	xmlNodeAddContent(date_node, BAD_CAST(buff));

	return doc;

}
