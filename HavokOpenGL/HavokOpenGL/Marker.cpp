#include "Marker.h"


Marker::Marker(float x, float y, float z, char* image)
{
	sx = x;
	sy = y;
	sz = z;
	setSize(sx, sy, sz);
	setPos(0.0,0.0,0.0);
	mr = 0.0;
	mg = 0.0;
	mb = 0.0;
	Dx = 1;
	Dy = 1;
	Dz = 1;
	LoadTextures *lt = new LoadTextures(image);  //for texture
	texture = lt->getTexture();
	delete lt;
}


Marker::~Marker(void)
{
}

void Marker::render(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);  
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, texture);
		glColor3f(mr, mg, mb);
		// Perform transformations here in TRS order
		glTranslatef(px, py, pz);
		//glRotatef(angle,hObj->getDir().x,hObj->getDir().y,hObj->getDir().z);
		drawFace(0, 4, 5, 1); // Draw each face
		drawFace(3, 7, 4, 0);
		drawFace(2, 6, 7, 3);
		drawFace(1, 5, 6, 2);
		drawFace(3, 0, 1, 2);
		drawFace(4, 7, 6, 5);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void Marker::drawFace(int v0, int v1, int v2, int v3){
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3f(verts[v0].x, verts[v0].y, verts[v0].z);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3f(verts[v1].x, verts[v1].y, verts[v1].z);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3f(verts[v2].x, verts[v2].y, verts[v2].z);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3f(verts[v3].x, verts[v3].y, verts[v3].z);
	glEnd();
}

void Marker::setSize(float sx,float sy, float sz){
	verts[0].set(-sx, sy, sz);
	verts[1].set( sx, sy, sz);
	verts[2].set( sx, sy,-sz);
	verts[3].set(-sx, sy,-sz);
	verts[4].set(-sx,-sy, sz);
	verts[5].set( sx,-sy, sz);
	verts[6].set( sx,-sy,-sz);
	verts[7].set(-sx,-sy,-sz);
}

void Marker::setPos(float x, float y, float z){
	px = x;
	py = y;
	pz = z;
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Marker::setRGB(float r, float g, float b){
	mr = r;
	mg = g;
	mb = b;
}

bool Marker::collides(Marker* mark){
	
	float hsxA = sx/2;
	float hsxB = mark->sx/2;
	if(px < mark->px){
		Dx = (mark->px - hsxB) - (px + hsxA);
	}
	else{
		Dx = (px - hsxB) - (mark->px + hsxA);
	}

	//float hsyA = sy/2;
	//float hsyB = mark->sy/2;
	//if(py < mark->py){
	//	Dy = (mark->py - hsyB) - (py + hsyA);
	//}
	//else{
	//	Dy = (py - hsyB) - (mark->py + hsyA);
	//}

	float hszA = sz/2;
	float hszB = mark->sz/2;
	if(pz < mark->pz){
		Dz = (mark->pz - hszB) - (pz + hszA);
	}
	else{
		Dz = (pz - hszB) - (mark->pz + hszA);
	}

	if(Dx <= 0 &&/* Dy <= 0 ||*/ Dz <= 0){
		return true;
	}
	else{
		return false;
	}
}


bool Marker::collidesBox(OGL_Box* cbox){
	
	float hsxA = sx/2;
	float hsxB = cbox->mx/2;
	if(px < cbox->getHavokObj()->getPos().x){
		Dx = (cbox->getHavokObj()->getPos().x - hsxB) - (px + hsxA);
	}
	else{
		Dx = (px - hsxB) - (cbox->getHavokObj()->getPos().x + hsxA);
	}

	//float hsyA = sy/2;
	//float hsyB = mark->sy/2;
	//if(py < mark->py){
	//	Dy = (mark->py - hsyB) - (py + hsyA);
	//}
	//else{
	//	Dy = (py - hsyB) - (mark->py + hsyA);
	//}

	float hszA = sz/2;
	float hszB = cbox->mz/2;
	if(pz < cbox->getHavokObj()->getPos().z){
		Dz = (cbox->getHavokObj()->getPos().z - hszB) - (pz + hszA);
	}
	else{
		Dz = (pz - hszB) - (cbox->getHavokObj()->getPos().z + hszA);
	}

	if(Dx <= 0 &&/* Dy <= 0 ||*/ Dz <= 0){
		return true;
	}
	else{
		return false;
	}
}

bool Marker::collidesWithSphere(OGL_Sphere* cSphere){
	float hsxA = sx/2;
	float hsxB = cSphere->csRadius;

	 p = cSphere->getHavokObj()->getPos().x;

	if(px < cSphere->getHavokObj()->getPos().x){
		Dx = (cSphere->getHavokObj()->getPos().x - hsxB) - (px + hsxA);
	}
	else{
		Dx = (px - hsxB) - (cSphere->getHavokObj()->getPos().x + hsxA);
	}

	float hszA = sz/2;
	float hszB = cSphere->csRadius;

	if(pz < cSphere->getHavokObj()->getPos().z){
		Dz = (cSphere->getHavokObj()->getPos().z - hszB) - (pz + hszA);
	}
	else{
		Dz = (pz - hszB) - (cSphere->getHavokObj()->getPos().z + hszA);
	}
	if(Dx <= 0 &&/* Dy <= 0 ||*/ Dz <= 0){
		return true;
	}
	else{
		return false;
	}
}

bool Marker::collidesWithSphereAndModel(OGL_Sphere* cSphere, Enemy* cEnemy){
	float hsxA = cEnemy->enemy->bb.xSize()/2;
	float hsxB = cSphere->csRadius;

	 p = cSphere->getHavokObj()->getPos().x;

	if(px > cSphere->getHavokObj()->getPos().x){
		Dx = (cSphere->getHavokObj()->getPos().x - hsxB) - (px + hsxA);
	}
	else{
		Dx = (px - hsxB) - (cSphere->getHavokObj()->getPos().x + hsxA);
	}

	float hszA = cEnemy->enemy->bb.zSize()/2;
	float hszB = cSphere->csRadius;

	if(pz > cSphere->getHavokObj()->getPos().z){
		Dz = (cSphere->getHavokObj()->getPos().z - hszB) - (pz + hszA);
	}
	else{
		Dz = (pz - hszB) - (cSphere->getHavokObj()->getPos().z + hszA);
	}
	if(Dx >= 0 &&/* Dy <= 0 ||*/ Dz >= 0){
		return true;
	}
	else{
		return false;
	}
}