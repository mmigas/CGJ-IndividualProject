#include "FrameBuffer.hpp"


void FrameBuffer::init(uint32_t id, uint32_t width, uint32_t height) {
    this->width = width;
    this->height = height;
    if (this->id == id) {
        glDeleteFramebuffers(1, &id);
        glDeleteTextures(1, &colorTexture);
        glDeleteTextures(1, &depthMap);
    }
    this->id = id;
    glGenFramebuffers(1, &this->id);
    glViewport(0, 0, width, height);
    attachColorTexture(width, height);
}


FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &this->id);
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    glViewport(0, 0, width, height);
}

void FrameBuffer::unBind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::resize(uint32_t width, uint32_t height) {
    if (width == 0 && height == 0) {
        return;
    }
    init(id, width, height);
}

void FrameBuffer::attachColorTexture(uint32_t width, uint32_t height) {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t FrameBuffer::getColorAttachmentRenderer() {
    return colorTexture;
}


void FrameBuffer::clear() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

uint32_t FrameBuffer::getID() {
    return id;
}