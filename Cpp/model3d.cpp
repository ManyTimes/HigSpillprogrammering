#include "../Header/model3d.h"

namespace cgl
{
	Model3D::Model3D()
	{
		// Initialize member data:
		data = NULL;
		filesize = 0;
		meshes = NULL;
		numMeshes = 0;
		numVertices = 0;
		totalFaces = 0;
	}

	Model3D::Model3D(const char *filename)
	{
		this->Load(filename);
	}

	void Model3D::Load(const char *filename)
	{
		// Open file
		std::fstream fp(filename, std::ios::in | std::ios::out | std::ios::binary);

		// Read file into buffer: data, and store file size
		if (fp.is_open()) 
		{
			fp.seekg(0, std::ios::end);
			filesize = fp.tellg();
			data = new char[filesize];
			fp.seekg(0, std::ios::beg);
			fp.read(data, filesize);
			data[filesize] = '\0';
			fp.close();
		}
		else 
		{
			cgl::Error("Could not open 3D file");
		}

		ChunkInfo_3ds *pointer = (ChunkInfo_3ds*)data;
		if(pointer->ID == MAIN3DS) 
		{
			unsigned char *version = (unsigned char*)(data+28);	// Find version.

			CountComponents();

			if(numMeshes)
				meshes = new Mesh3D[numMeshes];
			else return;										// We can't build anything without meshes.

			// Start processing mesh data
			ProcessData();

			// Convert our processed data into something OpenGL can render.
			ConvertData();
			
		}
		return;
	}

	void Model3D::CountComponents()
	{
		char *position = (data+16);

		while((position-data) < filesize)
		{
			ChunkInfo_3ds *info = (ChunkInfo_3ds*)position;
			switch(info->ID)
			{
				case EDIT3DS:
					position += 6;
					break;
				case EDIT_OBJECT:
					numMeshes++;
					position += info->length;
					break;
				default:
					position += info->length;
					break;
			}
		}
	}

	void Model3D::ProcessData()
	{
		char *position = (data+16);
		int meshIndex = -1;

		while((position-data) < filesize)
		{
			ChunkInfo_3ds *info = (ChunkInfo_3ds*)position;
			switch(info->ID)
			{
				case EDIT3DS:
					position += 6;
					break;
				case EDIT_OBJECT:
					position += 6;
					while(*position != NULL) position++;	// Apparently there's a string here, so we need to move past it
					position++;
					meshIndex++;
					break;
				case OBJ_TRIMESH:
					//position += info->length;
					position += 6;
					break;
				case TRI_VERTEXL:
					{
						meshes[meshIndex].numVertex = 0;
						meshes[meshIndex].numVertex = *(short*)(position+6);
						meshes[meshIndex].vertex = new Vertex3D[meshes[meshIndex].numVertex];

						float *fpointer = (float*)(position+8);
						for(int i = 0; i < meshes[meshIndex].numVertex; i++)
						{
							for(int ii = 0; ii < 3; ii++)
								meshes[meshIndex].vertex[i][ii] = fpointer[(i*3)+ii];

							// Swap y and z, opengl uses Y as up.
							std::swap(meshes[meshIndex].vertex[i][1],meshes[meshIndex].vertex[i][2]);

							// Models are mirrored for some reason, swap the vertices here and turn winding
							std::swap(meshes[meshIndex].vertex[i][0],meshes[meshIndex].vertex[i][2]);
						}

						position+=info->length;
						break;
					}
				case TRI_UWMAP:
					{
						meshes[meshIndex].numTexCoord = 0;
						meshes[meshIndex].numTexCoord = *(short*)(position+6);
						meshes[meshIndex].textureCoord = new TextureCoordinate3D[meshes[meshIndex].numTexCoord];

						float *fpointer = (float*)(position+8);
						for(int i = 0; i < meshes[meshIndex].numTexCoord; i++)
							for(int ii = 0; ii < 2;ii++)
								meshes[meshIndex].textureCoord[i][ii] = fpointer[(i*2)+ii];

						position+=info->length;
						break;
					}
				case TRI_FACEL1:
					{
						meshes[meshIndex].numFace = 0;
						meshes[meshIndex].numFace = *(short*)(position+6);
						meshes[meshIndex].face = new Face3D[meshes[meshIndex].numFace];
						// Also want possibility to have individual surface normals. 
						// Meaning we'll have to break up the indexing, since I've never found a way to
						// render a vertex with different normals attached in opengl. 1 Vertex, 1 Normal. Always together.
						meshes[meshIndex].normal = new Vertex3D[meshes[meshIndex].numFace];

						// Count our total faces:
						totalFaces += meshes[meshIndex].numFace;

						short *spointer = (short*)(position+8);
						for(int i = 0; i < meshes[meshIndex].numFace; i++)
						{
							short winding = spointer[(i*4)+3];
							Vector3f normal;
							Vector3f edge1, edge2;
							Vector3f points[3];

							for(int ii = 0; ii < 3; ii++)
							{
								meshes[meshIndex].face[i][ii] = (int)spointer[(i*4)+ii];
							}

							// Last part in fixing the mirroring from 3DS max, turn the winding.
							std::swap(meshes[meshIndex].face[i].f1, meshes[meshIndex].face[i].f3);

							VectorCopy(meshes[meshIndex].vertex[meshes[meshIndex].face[i].f1], points[0]);
							VectorCopy(meshes[meshIndex].vertex[meshes[meshIndex].face[i].f2], points[1]);
							VectorCopy(meshes[meshIndex].vertex[meshes[meshIndex].face[i].f3], points[2]);

							// The following 3 bits tell us how to draw the triangle.
							// Or they should, but they're always set, all of them?! Exported from 3DS weirdly.
							//if( winding & 1 ) // Winding A -> C
							//{
								edge1 = points[2] - points[0];
								edge2 = points[1] - points[0];
							//	edge1 = points[2] - points[0];
							//	edge2 = points[1] - points[2];
								edge1.Normalize();
								edge2.Normalize();
								normal = edge1.Cross(edge2);
							//}
							//else if( winding & 4 ) // Winding B -> C
							//{
							//	edge1 = points[0] - points[2];
							//	edge2 = points[2] - points[1];
							//	edge1.normalize();
							//	edge2.normalize();
							//	normal = edge1.cross(edge2);
							//}
							//if( winding & 4 ) // Winding A -> B

							VectorCopy(normal, meshes[meshIndex].normal[i]);
						}
						position+=info->length;
						break;
					}
				default:
					position += info->length;
					break;
			}
		}
	}

	void Model3D::ConvertData()
	{
		Vertex3D *vertexdata = new Vertex3D[totalFaces*3*2];		// Allocate vertex and normaldata in one go.
		Vertex3D *normaldata = &vertexdata[totalFaces*3];			// Set normaldata pointer

		int countFaces = 0;
		for(int i = 0; i < numMeshes; i++)
		{
			for(int ii = 0; ii < meshes[i].numFace; ii++)
			{
				for(int iii = 0; iii < MAXCOORDINATES; iii++)			//Max coordinates: x, y, z in a 3D enviornment
				{
					// Alternative 1:
					//vertexdata[(i*3)+ii].x = meshes[0].vertex[meshes[0].face[i][ii]].x;
					//vertexdata[(i*3)+ii].y = meshes[0].vertex[meshes[0].face[i][ii]].y;
					//vertexdata[(i*3)+ii].z = meshes[0].vertex[meshes[0].face[i][ii]].z;

					//// Alternative 2:
					//for(int iii = 0; iii < 3; iii++)
					//{
					//	vertexdata[(i*3)+ii][iii] = meshes[0].vertex[meshes[0].face[i][ii]][iii];	// <-- Oooo, not pretty.
					//	normaldata[(i*3)+ii][iii] = meshes[0].normal[meshes[0].face[i][ii]]
					//}

					// Alternative 3: (Going for this!)
					VectorCopy(meshes[i].vertex[meshes[i].face[ii][iii]], vertexdata[(countFaces*3)+(ii*3)+iii]);
					VectorCopy(meshes[i].normal[ii], normaldata[(countFaces*3)+(ii*3)+iii]);
					//normaldata[(i*3)+ii].z *= 300;
				}

			}
			countFaces += meshes[i].numFace;
		}

		glGenBuffers(1, &vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		//glBufferData(GL_ARRAY_BUFFER, meshes[0].numVertex*sizeof(Vertex3D), meshes[0].vertex, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, totalFaces*sizeof(Vertex3D)*3, vertexdata, GL_STATIC_DRAW);
		glGenBuffers(1, &normalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glBufferData(GL_ARRAY_BUFFER, totalFaces*sizeof(Vertex3D)*3, normaldata, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		delete[] vertexdata; // Also deallocates normaldata


		// Unfortunately we don't have any use of indexing, considering we want individual surface normals to be possible.
		//glGenBuffers(1, &indexVBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshes[0].numFace*sizeof(Face3D), meshes[0].face, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//delete meshes[0].vertex;
		//delete meshes[0].face;
	}

	void Model3D::Draw()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER,vertexVBO);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
		glVertexPointer(3, GL_FLOAT, 0/*sizeof(Vertex3D)*/, 0);
		glBindBuffer(GL_ARRAY_BUFFER,normalVBO);
		glNormalPointer(GL_FLOAT, 0, 0);//(char*)(NULL + offsetof(VertexData, normal)));

		glColor3f ( 0.2f, 0.2f, 0.2f ) ;
		//glDrawElements(GL_TRIANGLES, meshes[0].numFace*3, GL_UNSIGNED_SHORT, (GLvoid*)((char*)NULL));
		glDrawArrays(GL_TRIANGLES,0,totalFaces*3);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	void Model3D::Draw(float m[16])
	{
	//	std::cout << "M_3DS::Draw(float m[16]) not implemented";
		glPushMatrix();
			glMultMatrixf(m);
			Draw();
		glPopMatrix();
	//	glEnableClientState(GL_VERTEX_ARRAY);
	//	glEnableClientState(GL_NORMAL_ARRAY);
	//
	//	glBindBuffer(GL_ARRAY_BUFFER,vertexVBO);
	////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	//	glVertexPointer(3, GL_FLOAT, 0/*sizeof(Vertex3D)*/, 0);
	//	glBindBuffer(GL_ARRAY_BUFFER,normalVBO);
	//	glNormalPointer(GL_FLOAT, 0, 0);//(char*)(NULL + offsetof(VertexData, normal)));
	//
	//	glColor3f ( 0.2f, 0.2f, 0.2f ) ;
	//	//glDrawElements(GL_TRIANGLES, meshes[0].numFace*3, GL_UNSIGNED_SHORT, (GLvoid*)((char*)NULL));
	//	glDrawArrays(GL_TRIANGLES,0,totalFaces*3);
	//
	//	glDisableClientState(GL_VERTEX_ARRAY);
	//	glDisableClientState(GL_NORMAL_ARRAY);
	}
}//End Namespace