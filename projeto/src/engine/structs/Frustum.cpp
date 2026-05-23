#include "engine/structs/Frustum.hpp"

Frustum::Frustum() {
    // Inicialização das Planes
    for (int i = 0; i < 6; i++) {
        planes[i] = {0, 0, 0, 0};
    }
}

bool Frustum::pointInFrustum(float x, float y, float z) {
    for (int i = 0; i < 6; i++) {
        if (planes[i].a * x + planes[i].b * y + planes[i].c * z + planes[i].d < -1e-4f) {
            return false;
        }
    }
    return true;
}

bool Frustum::sphereInFrustum(float x, float y, float z, float radius) {
    for (int i = 0; i < 6; i++) {
        if (planes[i].a * x + planes[i].b * y + planes[i].c * z + planes[i].d < -radius - 1e-4f) {
            return false;
        }
    }
    return true;
}

void Frustum::updateFrustum(Camera* cam, float fov, float nearDist, float farDist, float ratio) {
    float pos[3] = {cam->getPosX(), cam->getPosY(), cam->getPosZ()};

    float d[3] = {
        cam->getLookX() - cam->getPosX(),
        cam->getLookY() - cam->getPosY(),
        cam->getLookZ() - cam->getPosZ()
    };
    normalize(d);
    if (d[0] == 0.0f && d[1] == 0.0f && d[2] == 0.0f) {
        return;
    }

    float up[3] = {cam->getUpX(), cam->getUpY(), cam->getUpZ()};
    normalize(up);
    if (up[0] == 0.0f && up[1] == 0.0f && up[2] == 0.0f) {
        up[0] = 0.0f;
        up[1] = 1.0f;
        up[2] = 0.0f;
    }

    float r[3];
    cross(d, up, r);
    normalize(r);
    if (r[0] == 0.0f && r[1] == 0.0f && r[2] == 0.0f) {
        float fallbackUp[3] = {0.0f, 1.0f, 0.0f};
        if (fabs(d[1]) > 0.9f) {
            fallbackUp[0] = 1.0f;
            fallbackUp[1] = 0.0f;
            fallbackUp[2] = 0.0f;
        }
        cross(d, fallbackUp, r);
        normalize(r);
        if (r[0] == 0.0f && r[1] == 0.0f && r[2] == 0.0f) {
            return;
        }
    }

    float u[3];
    cross(r, d, u);
    normalize(u);

    float fov_rad = fov * M_PI / 180.0f;
    float tanHalfFov = tanf(fov_rad * 0.5f);

    float nearH = 2.0f * tanHalfFov * nearDist;
    float nearW = nearH * ratio;
    float farH = 2.0f * tanHalfFov * farDist;
    float farW = farH * ratio;

    float nc[3] = {
        pos[0] + d[0] * nearDist,
        pos[1] + d[1] * nearDist,
        pos[2] + d[2] * nearDist
    };

    float fc[3] = {
        pos[0] + d[0] * farDist,
        pos[1] + d[1] * farDist,
        pos[2] + d[2] * farDist
    };

    float nh2 = nearH * 0.5f;
    float nw2 = nearW * 0.5f;
    float fh2 = farH * 0.5f;
    float fw2 = farW * 0.5f;

    float ntl[3] = {nc[0] + u[0] * nh2 - r[0] * nw2, nc[1] + u[1] * nh2 - r[1] * nw2, nc[2] + u[2] * nh2 - r[2] * nw2};
    float ntr[3] = {nc[0] + u[0] * nh2 + r[0] * nw2, nc[1] + u[1] * nh2 + r[1] * nw2, nc[2] + u[2] * nh2 + r[2] * nw2};
    float nbl[3] = {nc[0] - u[0] * nh2 - r[0] * nw2, nc[1] - u[1] * nh2 - r[1] * nw2, nc[2] - u[2] * nh2 - r[2] * nw2};
    float nbr[3] = {nc[0] - u[0] * nh2 + r[0] * nw2, nc[1] - u[1] * nh2 + r[1] * nw2, nc[2] - u[2] * nh2 + r[2] * nw2};

    float ftl[3] = {fc[0] + u[0] * fh2 - r[0] * fw2, fc[1] + u[1] * fh2 - r[1] * fw2, fc[2] + u[2] * fh2 - r[2] * fw2};
    float ftr[3] = {fc[0] + u[0] * fh2 + r[0] * fw2, fc[1] + u[1] * fh2 + r[1] * fw2, fc[2] + u[2] * fh2 + r[2] * fw2};
    float fbl[3] = {fc[0] - u[0] * fh2 - r[0] * fw2, fc[1] - u[1] * fh2 - r[1] * fw2, fc[2] - u[2] * fh2 - r[2] * fw2};
    float fbr[3] = {fc[0] - u[0] * fh2 + r[0] * fw2, fc[1] - u[1] * fh2 + r[1] * fw2, fc[2] - u[2] * fh2 + r[2] * fw2};

    createPlane(planes[0], ntr, fbr, nbr); // right
    createPlane(planes[1], nbl, ftl, ntl); // left
    createPlane(planes[2], nbr, fbl, nbl); // bottom
    createPlane(planes[3], ntl, ftr, ntr); // top
    createPlane(planes[4], ftl, fbl, fbr); // far
    createPlane(planes[5], ntr, nbl, ntl); // near
/*
    float probe[3] = {
        pos[0] + d[0] * ((nearDist + farDist) * 0.5f),
        pos[1] + d[1] * ((nearDist + farDist) * 0.5f),
        pos[2] + d[2] * ((nearDist + farDist) * 0.5f)
    };

    for (int i = 0; i < 6; i++) {
        float side = planes[i].a * probe[0] + planes[i].b * probe[1] + planes[i].c * probe[2] + planes[i].d;
        if (side < 0.0f) {
            planes[i].a = -planes[i].a;
            planes[i].b = -planes[i].b;
            planes[i].c = -planes[i].c;
            planes[i].d = -planes[i].d;
        }
    }

*/ 
 
}

void Frustum::createPlane(Plane& plane, float* p1, float* p2, float* p3){
    float v1[3] = {p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]};
    float v2[3] = {p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]};
    float normal[3];

    cross(v1, v2, normal);
    normalize(normal);

    plane.a = normal[0];
    plane.b = normal[1];
    plane.c = normal[2];
    plane.d = -(normal[0] * p1[0] + normal[1] * p1[1] + normal[2] * p1[2]);
}

void Frustum::drawFrustum(Camera* cam, float fov, float nearDist, float farDist, float ratio) {
    float pos[3] = {cam->getPosX(), cam->getPosY(), cam->getPosZ()};

    float d[3] = {
        cam->getLookX() - cam->getPosX(),
        cam->getLookY() - cam->getPosY(),
        cam->getLookZ() - cam->getPosZ()
    };
    normalize(d);
    if (d[0] == 0.0f && d[1] == 0.0f && d[2] == 0.0f) {
        return;
    }

    float up[3] = {cam->getUpX(), cam->getUpY(), cam->getUpZ()};
    normalize(up);
    if (up[0] == 0.0f && up[1] == 0.0f && up[2] == 0.0f) {
        up[0] = 0.0f;
        up[1] = 1.0f;
        up[2] = 0.0f;
    }

    float r[3];
    cross(d, up, r);
    normalize(r);
    if (r[0] == 0.0f && r[1] == 0.0f && r[2] == 0.0f) {
        float fallbackUp[3] = {0.0f, 1.0f, 0.0f};
        if (fabs(d[1]) > 0.9f) {
            fallbackUp[0] = 1.0f;
            fallbackUp[1] = 0.0f;
            fallbackUp[2] = 0.0f;
        }
        cross(d, fallbackUp, r);
        normalize(r);
        if (r[0] == 0.0f && r[1] == 0.0f && r[2] == 0.0f) {
            return;
        }
    }

    float u[3];
    cross(r, d, u);
    normalize(u);

    float fov_rad = fov * M_PI / 180.0f;
    float tanHalfFov = tanf(fov_rad * 0.5f);

    float nearH = 2.0f * tanHalfFov * nearDist;
    float nearW = nearH * ratio;
    float farH = 2.0f * tanHalfFov * farDist;
    float farW = farH * ratio;

    float nc[3] = {
        pos[0] + d[0] * nearDist,
        pos[1] + d[1] * nearDist,
        pos[2] + d[2] * nearDist
    };

    float fc[3] = {
        pos[0] + d[0] * farDist,
        pos[1] + d[1] * farDist,
        pos[2] + d[2] * farDist
    };

    float nh2 = nearH * 0.5f;
    float nw2 = nearW * 0.5f;
    float fh2 = farH * 0.5f;
    float fw2 = farW * 0.5f;

    float ntl[3] = {nc[0] + u[0] * nh2 - r[0] * nw2, nc[1] + u[1] * nh2 - r[1] * nw2, nc[2] + u[2] * nh2 - r[2] * nw2};
    float ntr[3] = {nc[0] + u[0] * nh2 + r[0] * nw2, nc[1] + u[1] * nh2 + r[1] * nw2, nc[2] + u[2] * nh2 + r[2] * nw2};
    float nbl[3] = {nc[0] - u[0] * nh2 - r[0] * nw2, nc[1] - u[1] * nh2 - r[1] * nw2, nc[2] - u[2] * nh2 - r[2] * nw2};
    float nbr[3] = {nc[0] - u[0] * nh2 + r[0] * nw2, nc[1] - u[1] * nh2 + r[1] * nw2, nc[2] - u[2] * nh2 + r[2] * nw2};

    float ftl[3] = {fc[0] + u[0] * fh2 - r[0] * fw2, fc[1] + u[1] * fh2 - r[1] * fw2, fc[2] + u[2] * fh2 - r[2] * fw2};
    float ftr[3] = {fc[0] + u[0] * fh2 + r[0] * fw2, fc[1] + u[1] * fh2 + r[1] * fw2, fc[2] + u[2] * fh2 + r[2] * fw2};
    float fbl[3] = {fc[0] - u[0] * fh2 - r[0] * fw2, fc[1] - u[1] * fh2 - r[1] * fw2, fc[2] - u[2] * fh2 - r[2] * fw2};
    float fbr[3] = {fc[0] - u[0] * fh2 + r[0] * fw2, fc[1] - u[1] * fh2 + r[1] * fw2, fc[2] - u[2] * fh2 + r[2] * fw2};
    
    glBegin(GL_LINES);
        // Near plane
        glVertex3f(ntl[0], ntl[1], ntl[2]);
        glVertex3f(ntr[0], ntr[1], ntr[2]);
        glVertex3f(ntr[0], ntr[1], ntr[2]);
        glVertex3f(nbr[0], nbr[1], nbr[2]);
        glVertex3f(nbr[0], nbr[1], nbr[2]);
        glVertex3f(nbl[0], nbl[1], nbl[2]);
        glVertex3f(nbl[0], nbl[1], nbl[2]);
        glVertex3f(ntl[0], ntl[1], ntl[2]);

        // Far plane
        glVertex3f(ftl[0], ftl[1], ftl[2]);
        glVertex3f(ftr[0], ftr[1], ftr[2]);
        glVertex3f(ftr[0], ftr[1], ftr[2]);
        glVertex3f(fbr[0], fbr[1], fbr[2]);
        glVertex3f(fbr[0], fbr[1], fbr[2]);
        glVertex3f(fbl[0], fbl[1], fbl[2]);
        glVertex3f(fbl[0], fbl[1], fbl[2]);
        glVertex3f(ftl[0], ftl[1], ftl[2]);

        // Connect near and far planes
        glVertex3f(ntl[0], ntl[1], ntl[2]);
        glVertex3f(ftl[0], ftl[1], ftl[2]);

        glVertex3f(ntr[0], ntr[1], ntr[2]);
        glVertex3f(ftr[0], ftr[1], ftr[2]);

        glVertex3f(nbl[0], nbl[1], nbl[2]);
        glVertex3f(fbl[0], fbl[1], fbl[2]);

        glVertex3f(nbr[0], nbr[1], nbr[2]);
        glVertex3f(fbr[0], fbr[1], fbr[2]);
    glEnd();
}