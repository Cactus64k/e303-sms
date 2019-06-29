#include "chunks.h"

int main(int argc, char *argv[])
{
	int status = EXIT_SUCCESS;

	if(argc != 3)
	{
		fprintf(stderr, "modem-sms [number] [content] \n");
		status = EXIT_FAILURE;
	}
	else
	{
		char* phone = argv[1];
		char* content = argv[2];

		CURL* curl	= curl_easy_init();

		if(curl != NULL)
		{
			xmlDocPtr xml_doc	= create_request(content, phone);
			xmlChar* request	= NULL;
			int buff_size		= 0;

			xmlDocDumpMemoryEnc(xml_doc, &request, &buff_size, "UTF-8");
			xmlFreeDoc(xml_doc);

			xmlParserCtxtPtr ctxt = xmlCreatePushParserCtxt(NULL, NULL, NULL, 0, NULL);

			curl_easy_setopt(curl, CURLOPT_URL, URL);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, ctxt);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, buff_size);

			CURLcode res = curl_easy_perform(curl);
			if(res == CURLE_OK)
			{
				xmlParseChunk(ctxt, NULL, 0, 1);

				if(ctxt->wellFormed == 1)
				{
					xmlDocPtr doc		= ctxt->myDoc;
					xmlNode* root		= xmlDocGetRootElement(doc);
					xmlChar* content	= get_xml_node_content(root, "response");

					if(content != NULL)
						printf("SMS: %s\n", content);

					xmlFree(content);
					xmlFreeDoc(doc);
				}
				else
				{
					fprintf(stderr, "ERROR: failed to parse xml\n");
					status = EXIT_FAILURE;
				}
			}
			else
			{
				fprintf(stderr, "ERROR: %s\n", curl_easy_strerror(res));
				status = EXIT_FAILURE;
			}

			curl_easy_cleanup(curl);
			xmlFreeParserCtxt(ctxt);
			xmlCleanupParser();
			xmlFree(request);

		}
		else
			status = EXIT_FAILURE;
	}

	return status
}
