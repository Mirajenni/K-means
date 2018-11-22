#include "GrafoXML.h"
#include "Grafo.h"
#include "tinyxml.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
std::string str;
int tamanhoNO;
int tamanhoARESTA;

int datas;
NO *no[10000];
ARESTA *aresta[10000];


int lerXML() {
	TiXmlDocument doc("grafo_teste1.graphml");
	if (!doc.LoadFile()) {
		printf("Nao leu!\n");
		return 0;
	}
	else {
		TiXmlElement* root = doc.FirstChildElement();

		if (root == NULL)
		{
			cerr << "Failed to load file: No root element."
				<< endl;
			doc.Clear();
			return 0;
		}
		//Percorrer até NODE
		TiXmlElement *elem;
		for (elem = root->FirstChildElement(); elem->NextSibling() != NULL; elem = elem->NextSiblingElement()) {

		}
		elem = elem->FirstChildElement();
		for (; elem != NULL; elem = elem->NextSiblingElement())
		{
			string elemName = elem->Value();
			cout << "Elem name " << elemName << endl;

			if (elemName == "node")
			{

				//Cria O NO 
				NO *aux = new NO;
				aux->label = "nada";
				aux->size = 0;
				aux->r = 0;
				aux->g = 0;
				aux->b = 0;
				aux->x = 0;
				aux->y = 0;
				aux->prox = NULL;

				const char *attr = elem->Attribute("id");
				if (attr != NULL)
					cout << "Achei o id " << attr << endl;
				aux->id = attr;

				TiXmlElement *proxElem = elem->FirstChildElement();
				for (; proxElem != NULL; proxElem = proxElem->NextSiblingElement()) {
					//Pega tudo dentro de data key pra colocar no NÓ
					const char *attr = proxElem->Attribute("key");
					if (strcmp(attr, "label") == 0) {
						aux->label = proxElem->GetText();
						cout << "n label " << aux->label << endl;
					}
					else if (strcmp(attr, "size") == 0) {
						string attr = proxElem->GetText();
						aux->size = stof((attr).c_str(), 0);
						cout << "n size " << aux->size << endl;
					}

					else if (strcmp(attr, "r") == 0) {
						int r = atoi(proxElem->GetText());
						aux->r = r;
						cout << "n r " << aux->r << endl;
					}
					else if (strcmp(attr, "g") == 0) {
						int g = atoi(proxElem->GetText());
						aux->g = g;
						cout << "n g " << aux->g << endl;
					}
					else if (strcmp(attr, "b") == 0) {
						int b = atoi(proxElem->GetText());
						aux->b = b;
						cout << "n b " << aux->b << endl;
					}
					else if (strcmp(attr, "x") == 0) {
						string attr = proxElem->GetText();
						aux->x = stof((attr).c_str(), 0);
						cout << "n x " << aux->x << endl;
					}
					else if (strcmp(attr, "y") == 0) {
						string attr = proxElem->GetText();
						aux->y = stof((attr).c_str(), 0);
						printf("n y %f\n\n\n", (aux->y));
					}

					no[tamanhoNO] = aux;
				}
				tamanhoNO++;
			}
			else if (elemName == "edge") {
				//Cria ARESTAS QUE LIGAM A LISTA
				ARESTA *ar = new ARESTA;
				ar->id = "nada";
				ar->source = "nada";
				ar->target = "nada";
				ar->weight = 0;
				ar->prox = NULL;

				const char *attr = elem->Attribute("id");
				ar->id = attr;

				cout << "aresta id     " << ar->id << endl;


				/*TiXmlElement *proxElem = elem->FirstChildElement();
				for (; proxElem != NULL; proxElem = proxElem->NextSiblingElement()) {
					TiXmlAttribute *pAttr = elem->FirstAttribute();
					for (; strcmp(pAttr->Name(), "source") == 0; pAttr = pAttr->Next())
					{
						if (strcmp(pAttr->Name(), "source") == 0) {
							ar->source = pAttr->Value();
							cout << "Aux source        " << ar->source << endl;
						}
						else if (strcmp(pAttr->Name(), "target") == 0) {
							ar->target = pAttr->Value();
							cout << "aux target          " << ar->target << endl;
						}

						else if (strcmp(pAttr->Name(), "weight") == 0) {
							cout << "peso?       " << pAttr->Value() << endl;
						}
					}
				}*/
				TiXmlElement *prox = elem->FirstChildElement();
				//Pega o weight em data key pra colocar na ARESTA
				const char *att = prox->Attribute("key");
				if (strcmp(att, "weight") == 0) {
					att = prox->GetText();
					ar->weight = atof(att);
					cout << "peso aresta    " << ar->weight << endl;
				}

				aresta[tamanhoARESTA] = ar;
				tamanhoARESTA++;
			}
		}
		doc.Clear();
		return 1;
	}
}


int salvarXML() {
	TiXmlDocument doc;

	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "UTF-8" "", "");
	doc.LinkEndChild(decl);

	TiXmlElement* root = new TiXmlElement("graphml");
	doc.LinkEndChild(root);
	root->SetAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns");

	TiXmlElement* key1 = new TiXmlElement("key");
	root->LinkEndChild(key1);
	key1->SetAttribute("attr.name", "label");
	key1->SetAttribute("attr.type", "string");
	key1->SetAttribute("for", "node");
	key1->SetAttribute("id", "label");

	TiXmlElement* key2 = new TiXmlElement("key");
	root->LinkEndChild(key2);
	key2->SetAttribute("attr.name", "Edge Label");
	key2->SetAttribute("attr.type", "string");
	key2->SetAttribute("for", "edge");
	key2->SetAttribute("id", "edgelabel");

	TiXmlElement* key3 = new TiXmlElement("key");
	root->LinkEndChild(key3);
	key3->SetAttribute("attr.name", "weight");
	key3->SetAttribute("attr.type", "double");
	key3->SetAttribute("for", "edge");
	key3->SetAttribute("id", "weight");

	TiXmlElement* key4 = new TiXmlElement("key");
	root->LinkEndChild(key4);
	key4->SetAttribute("attr.name", "r");
	key4->SetAttribute("attr.type", "int");
	key4->SetAttribute("for", "node");
	key4->SetAttribute("id", "r");

	TiXmlElement* key5 = new TiXmlElement("key");
	root->LinkEndChild(key5);
	key5->SetAttribute("attr.name", "g");
	key5->SetAttribute("attr.type", "int");
	key5->SetAttribute("for", "node");
	key5->SetAttribute("id", "g");

	TiXmlElement* key6 = new TiXmlElement("key");
	root->LinkEndChild(key6);
	key6->SetAttribute("attr.name", "b");
	key6->SetAttribute("attr.type", "int");
	key6->SetAttribute("for", "node");
	key6->SetAttribute("id", "b");


	TiXmlElement* key7 = new TiXmlElement("key");
	root->LinkEndChild(key7);
	key7->SetAttribute("attr.name", "x");
	key7->SetAttribute("attr.type", "float");
	key7->SetAttribute("for", "node");
	key7->SetAttribute("id", "x");

	TiXmlElement* key8 = new TiXmlElement("key");
	root->LinkEndChild(key8);
	key8->SetAttribute("attr.name", "y");
	key8->SetAttribute("attr.type", "float");
	key8->SetAttribute("for", "node");
	key8->SetAttribute("id", "y");


	TiXmlElement* key9 = new TiXmlElement("key");
	root->LinkEndChild(key9);
	key9->SetAttribute("attr.name", "size");
	key9->SetAttribute("attr.type", "float");
	key9->SetAttribute("for", "node");
	key9->SetAttribute("id", "size");

	TiXmlElement* graph = new TiXmlElement("graph");
	root->LinkEndChild(graph);
	graph->SetAttribute("edgedefault", "directed");


	//Fazer um for aqui pra cada elemento da lista de adjacencia ou matriz de adjacencia
	for (int i = 0; i < tamanhoNO; i++) {
		TiXmlElement* node = new TiXmlElement("node");
		graph->LinkEndChild(node);

		const char *no_id = no[i]->id.c_str();
		node->SetAttribute("id", no_id);

		TiXmlElement* data1 = new TiXmlElement("data");
		node->LinkEndChild(data1);
		data1->SetAttribute("key", "label");
		const char *label = no[i]->label.c_str();
		data1->LinkEndChild(new TiXmlText(label));

		TiXmlElement* data2 = new TiXmlElement("data");
		node->LinkEndChild(data2);
		data2->SetAttribute("key", "size");

		std::ostringstream size;
		size << no[i]->size;
		std::string s(size.str());
		const char *no_size = s.c_str();
		data2->LinkEndChild(new TiXmlText(no_size));

		TiXmlElement* data3 = new TiXmlElement("data");
		node->LinkEndChild(data3);
		data3->SetAttribute("key", "r");
		std::string r1 = std::to_string(no[i]->r);
		char const *no_r = r1.c_str();
		data3->LinkEndChild(new TiXmlText(no_r));

		TiXmlElement* data4 = new TiXmlElement("data");
		node->LinkEndChild(data4);
		data4->SetAttribute("key", "g");
		std::string g1 = std::to_string(no[i]->g);
		char const *no_g = g1.c_str();
		data4->LinkEndChild(new TiXmlText(no_g));

		TiXmlElement* data5 = new TiXmlElement("data");
		node->LinkEndChild(data5);
		data5->SetAttribute("key", "b");
		std::string b1 = std::to_string(no[i]->b);
		char const *no_b = b1.c_str();
		data5->LinkEndChild(new TiXmlText(no_b));

		TiXmlElement* data6 = new TiXmlElement("data");
		node->LinkEndChild(data6);
		data6->SetAttribute("key", "x");
		std::ostringstream x;
		x << no[i]->x;
		std::string x1(x.str());
		const char *no_x = x1.c_str();
		data6->LinkEndChild(new TiXmlText(no_x));

		TiXmlElement* data7 = new TiXmlElement("data");
		node->LinkEndChild(data7);
		data7->SetAttribute("key", "y");
		std::ostringstream y;
		y << no[i]->y;
		std::string y1(y.str());
		const char *no_y = y1.c_str();
		data7->LinkEndChild(new TiXmlText(no_y));
	}
	for (int i = 0; i < tamanhoARESTA; i++) {
		TiXmlElement* edge1 = new TiXmlElement("edge");
		graph->LinkEndChild(edge1);
		const char *ar_id = aresta[i]->id.c_str();
		const char *ar_source = aresta[i]->source.c_str();
		const char *ar_target = aresta[i]->target.c_str();
		edge1->SetAttribute("id", ar_id);
		edge1->SetAttribute("source", ar_source);
		edge1->SetAttribute("target", ar_target);

		TiXmlElement* dataWeight = new TiXmlElement("data");
		edge1->LinkEndChild(dataWeight);
		dataWeight->SetAttribute("key", "weight");
		std::ostringstream weight;
		weight << aresta[i]->weight;
		std::string w(weight.str());
		const char *no_weight = w.c_str();
		dataWeight->LinkEndChild(new TiXmlText(no_weight));
	}

	bool success = doc.SaveFile("novo_grafo.graphml");
	doc.Clear();
	if (success)
		return 1;
	else
		return 0;
}



