#include "chunks.h"

xmlChar* get_xml_node_content(xmlNode* node, char* name)
{
	while(node != NULL)
	{
		if(node->type == XML_ELEMENT_NODE)
		{
			if(strcmp((char*)node->name, name) == 0)
			{
				xmlChar* content = xmlNodeGetContent(node);
				return content;
			}
		}

		node = node->next;
	}
	return NULL;
}
