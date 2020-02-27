#pragma once

// FBX
#include <fbxsdk.h>
#include <iostream>
#include "Mesh.h"

#define RAND_NORMAL XMFLOAT3(rand()/float(RAND_MAX),rand()/float(RAND_MAX),rand()/float(RAND_MAX))


class Importer
{
	wstring file_with_extention;



public:

	FbxScene* ImporterFbx(const char* filename);
	SimpleMesh ProcessFbxMesh(FbxScene* scene);

};

FbxScene* ImporterFbx(const char* filename)
{
	const char* lFilename = filename;

	// Initialize the SDK manager. This object handles memory management.
	FbxManager* lSdkManager = FbxManager::Create();

	// Create the IO settings object.
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	// Use the first argument as the filename for the importer.
	if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings()))
	{
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
		exit(-1);
	}


	// Create a new scene so that it can be populated by the imported file.
	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	// The file is imported, so get rid of the importer.
	lImporter->Destroy();

	// Process the scene and build DirectX Arrays
	//ProcessFbxMesh(lScene);
	return lScene;
}

SimpleMesh ProcessFbxMesh(FbxScene* scene)
{
	SimpleMesh simpleMesh;
	
	// set up output console
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	FbxNode* Node = scene->GetRootNode();
	//FBX Mesh stuff
	int childrenCount = Node->GetChildCount();

	cout << "\nName:" << Node->GetName();

	for (int i = 0; i < childrenCount; i++)
	{
		FbxNode* childNode = Node->GetChild(i);
		FbxMesh* mesh = childNode->GetMesh();

		if (mesh != NULL)
		{
			cout << "\nMesh:" << childNode->GetName();

			// Get index count from mesh
			int numVertices = mesh->GetControlPointsCount();
			cout << "\nVertex Count:" << numVertices;

			// Resize the vertex vector to size of this mesh
			simpleMesh.vertexList.resize(numVertices);

			//================= Process Vertices ===============
			for (int j = 0; j < numVertices; j++)
			{
				FbxVector4 vert = mesh->GetControlPointAt(j);
				simpleMesh.vertexList[j].Pos.x = (float)vert.mData[0] / 50.0f;
				simpleMesh.vertexList[j].Pos.y = (float)vert.mData[1] / 50.0f;
				simpleMesh.vertexList[j].Pos.z = (float)vert.mData[2] / 50.0f;
				// Generate random normal for first attempt at getting to render
				simpleMesh.vertexList[j].Normal = RAND_NORMAL;
			}

			int numIndices = mesh->GetPolygonVertexCount();
			cout << "\nIndice Count:" << numIndices;

			// No need to allocate int array, FBX does for us
			int* indices = mesh->GetPolygonVertices();

			// Fill indiceList
			simpleMesh.indicesList.resize(numIndices);
			memcpy(simpleMesh.indicesList.data(), indices, numIndices * sizeof(int));


			// Part 2, goes here?
			// Get the Normals array from the mesh
			FbxArray<FbxVector4> normalsVec;
			mesh->GetPolygonVertexNormals(normalsVec);
			cout << "\nNormalVec Count:" << normalsVec.Size();

			// Declare a new array for the second vertex array
			// Note the size is numIndices not numVertices
			vector<SimpleVertex> vertexListExpanded;
			vertexListExpanded.resize(numIndices);

			//FbxArray<FbxVector4> normalsVec;
			//mesh->GetPolygonVertexNormals(normalsVec);
			//cout << "\nNormalVec Count: " << normalsVec.Size();
			//get all UV set names
			FbxStringList lUVSetNameList;
			mesh->GetUVSetNames(lUVSetNameList);
			//get lUVSetIndex-th uv set
			const char* lUVSetName = lUVSetNameList.GetStringAt(0);
			const FbxGeometryElementUV* lUVElement = mesh->GetElementUV(lUVSetName);
			//const FbxGeometryElementNormal* lNormElement = mesh->GetElementNormal();

			// align (expand) vertex array and set the normals
			for (int j = 0; j < numIndices; j++)
			{
				vertexListExpanded[j].Pos.x = simpleMesh.vertexList[indices[j]].Pos.x;
				vertexListExpanded[j].Pos.y = simpleMesh.vertexList[indices[j]].Pos.y;
				vertexListExpanded[j].Pos.z = simpleMesh.vertexList[indices[j]].Pos.z;
				vertexListExpanded[j].Normal.x = normalsVec.GetAt(j)[0];
				vertexListExpanded[j].Normal.y = normalsVec.GetAt(j)[1];
				vertexListExpanded[j].Normal.z = normalsVec.GetAt(j)[2];

				// texture coords
				if (lUVElement->GetReferenceMode() == FbxLayerElement::eDirect)
				{
					FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(indices[j]);

					vertexListExpanded[j].Tex.x = lUVValue[0];
					vertexListExpanded[j].Tex.y = 1.0f - lUVValue[1];
					vertexListExpanded[j].Tex.z = 0;

				}
				else if (lUVElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				{
					auto& index_array = lUVElement->GetIndexArray();

					FbxVector2 lUVValue = lUVElement->GetDirectArray().GetAt(index_array[j]);

					vertexListExpanded[j].Tex.x = lUVValue[0];
					vertexListExpanded[j].Tex.y = 1.0f - lUVValue[1];
					vertexListExpanded[j].Tex.z = 0;
				}

				//// normals
				//const FbxGeometryElementNormal* lNormElement = mesh->GetElementNormal(0);
				//if (lNormElement->GetReferenceMode() == FbxLayerElement::eDirect)
				//{
				//	FbxVector4 lnormValue = lNormElement->GetDirectArray().GetAt(indices[j]);

				//	vertexListExpanded[j].Normal.x = lnormValue.mData[0];
				//	vertexListExpanded[j].Normal.y = lnormValue.mData[1];
				//	vertexListExpanded[j].Normal.z = lnormValue.mData[2];
				//}
				//else if (lNormElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				//{
				//	auto& index_array = lNormElement->GetIndexArray();

				//	FbxVector4 lnormValue = lNormElement->GetDirectArray().GetAt(index_array[j]);

				//	vertexListExpanded[j].Normal.x = lnormValue.mData[0];
				//	vertexListExpanded[j].Normal.y = lnormValue.mData[1];
				//	vertexListExpanded[j].Normal.z = lnormValue.mData[2];
				//}
			}

			// make new indices to match the new vertex(2) array
			vector<int> indicesList;
			indicesList.resize(numIndices);

			for (int j = 0; j < numIndices; j++)
			{
				indicesList[j] = j;
			}
			//vector<SimpleVertex>compactedVertexList;
			//vector<int>indicesList;
			//if (true)
			//{
			//	//Compactify();


			//	indicesList.clear();
			//	float episilon = 0.001f;
			//	int compactedIndex = 0;
			//	for (int i = 0; i < numIndices; i++)
			//	{
			//		bool found = false;
			//		int  foundVertex = 0;
			//		for (int j = 0; j < compactedVertexList.size(); j++)
			//		{
			//			if (abs(vertexListExpanded[i].Pos.x - compactedVertexList[j].Pos.x) <= episilon &&
			//				abs(vertexListExpanded[i].Pos.y - compactedVertexList[j].Pos.y) <= episilon &&
			//				abs(vertexListExpanded[i].Pos.z - compactedVertexList[j].Pos.z) <= episilon &&
			//				abs(vertexListExpanded[i].Normal.x - compactedVertexList[j].Normal.x) <= episilon &&
			//				abs(vertexListExpanded[i].Normal.y - compactedVertexList[j].Normal.y) <= episilon &&
			//				abs(vertexListExpanded[i].Normal.z - compactedVertexList[j].Normal.z) <= episilon
			//				)
			//			{
			//				found = true;
			//				indicesList.push_back(j);

			//				break;
			//			}
			//		}
			//		if (!found)
			//		{
			//			compactedVertexList.push_back(vertexListExpanded[i]);
			//			indicesList.push_back(compactedVertexList.size() - 1);
			//		}
			//	}


			//	simpleMesh.indicesList.assign(indicesList.begin(), indicesList.end());
			//	simpleMesh.vertexList.assign(compactedVertexList.begin(), compactedVertexList.end());

			//}
			//else
			//{
				simpleMesh.indicesList.assign(indicesList.begin(), indicesList.end());
				simpleMesh.vertexList.assign(vertexListExpanded.begin(), vertexListExpanded.end());
			//}
			//// print out some stats
			//cout << "\nindex count BEFORE/AFTER compaction " << numIndices;
			//cout << "\nvertex count ORIGINAL (FBX source): " << numVertices;
			//cout << "\nvertex count AFTER expansion: " << vertexListExpanded.size();
			//cout << "\nvertex count AFTER compaction: " << compactedVertexList.size();
			//cout << "\nSize reduction: " << ((vertexListExpanded.size() - compactedVertexList.size()) / (float)vertexListExpanded.size()) * 100.00f << "%";
			//cout << "\nor " << (compactedVertexList.size() / (float)numVertices) << " of the expanded size";

			//================= Texture ========================================

			int materialCount = childNode->GetSrcObjectCount<FbxSurfaceMaterial>();

			for (int index = 0; index < materialCount; index++)
			{
				FbxSurfaceMaterial* material = (FbxSurfaceMaterial*)childNode->GetSrcObject<FbxSurfaceMaterial>(index);

				if (material != NULL)
				{
					cout << "\nmaterial: " << material->GetName() << std::endl;
					// This only gets the material of type sDiffuse, you probably need to traverse all Standard Material Property by its name to get all possible textures.
					FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

					// Check if it's layeredtextures
					int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

					if (layeredTextureCount > 0)
					{
						for (int j = 0; j < layeredTextureCount; j++)
						{
							FbxLayeredTexture* layered_texture = FbxCast<FbxLayeredTexture>(prop.GetSrcObject<FbxLayeredTexture>(j));
							int lcount = layered_texture->GetSrcObjectCount<FbxTexture>();

							for (int k = 0; k < lcount; k++)
							{
								FbxFileTexture* texture = FbxCast<FbxFileTexture>(layered_texture->GetSrcObject<FbxTexture>(k));
								// Then, you can get all the properties of the texture, include its name
								const char* textureName = texture->GetFileName();
								cout << textureName;
							}
						}
					}
					else
					{
						// Directly get textures
						int textureCount = prop.GetSrcObjectCount<FbxTexture>();
						for (int j = 0; j < textureCount; j++)
						{
							FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxTexture>(j));
							// Then, you can get all the properties of the texture, include its name
							const char* textureName = texture->GetFileName();
							string temp = (string)textureName;
							string::size_type const end(temp.find_last_of('.'));
							string::size_type const start(temp.find_last_of('/\\'));
							string file_without_extension = temp.substr(start + 1, temp.size() - end + 1);
							file_without_extension = file_without_extension.append(".dds");
							file_without_extension.insert(0, "\Assets\\");
							cout << file_without_extension;
							//file_with_extention = wstring(file_without_extension.begin(), file_without_extension.end());

							FbxProperty p = texture->RootProperty.Find("Crate");

							cout << p.Get<FbxString>() << std::endl;

						}
					}
				}
			}
		}
		//ProcessFbxMesh(childNode);
	}
	return simpleMesh;
}
