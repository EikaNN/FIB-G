#include "model-info.h"
#include "glwidget.h"
#include <iostream>
using namespace std;

void ModelInfo::printModelInfo()
{
	Scene* scn = scene();
	int nobj, npol, nver, ntri;
    const vector<Object> &objects = scn->objects();
	nobj = objects.size();
	npol = nver = ntri = 0;
	for (int i = 0; i < nobj; ++i)
	{
        const Object &obj = objects[i];
        nver += obj.vertices().size();
        const vector<Face> &faces = obj.faces();
		npol += faces.size();
		for (int j = 0; j < npol; ++j)
		{
			if (faces[j].numVertices() == 3) ++ntri;
		}
	}
	cout << "Numero total objectes " << nobj << endl;
	cout << "Numero total de poligons " << npol << endl;
	cout << "Numero total de vertexs " << nver << endl;
    cout << "Percentatge de triangles " << ntri/double(npol)*100 << '%' << endl;
}

void ModelInfo::onPluginLoad()
{
    this->glwidget()->clearScene();
    printModelInfo();
}

void ModelInfo::onObjectAdd()
{
	printModelInfo();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(model-info, ModelInfo)   // plugin name, plugin class
#endif
