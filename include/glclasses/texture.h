#pragma once

#include "resource.h"
#include <string>
#include <initializer_list>
#include <algorithm>

namespace glc {

    namespace internal {
        inline int getMipmapLevels(std::initializer_list<int> dims){
            return 1 + std::floor(std::log2(std::max(dims)));
        }
        template <typename T>
        struct glconst4type
        {
            static_assert( std::is_same<T, void>::value,  "Invalid type!" );
            static constexpr GLenum value = 0;
        };

        template <> struct glconst4type<unsigned char>  {static constexpr GLenum value = GL_UNSIGNED_BYTE;};
        template <> struct glconst4type<signed char>    {static constexpr GLenum value = GL_BYTE;};
        template <> struct glconst4type<char>           {static constexpr GLenum value = std::numeric_limits<char>::is_signed ? GL_BYTE : GL_UNSIGNED_BYTE;};
        template <> struct glconst4type<unsigned short> {static constexpr GLenum value = GL_UNSIGNED_SHORT;};
        template <> struct glconst4type<signed short>   {static constexpr GLenum value = GL_SHORT;};
        template <> struct glconst4type<unsigned int>   {static constexpr GLenum value = GL_UNSIGNED_INT;};
        template <> struct glconst4type<signed int>     {static constexpr GLenum value = GL_INT;};
        template <> struct glconst4type<float>          {static constexpr GLenum value = GL_FLOAT;};
        template <> struct glconst4type<double>         {static constexpr GLenum value = GL_DOUBLE;};
    }

    enum class TextureFilterModeMag : GLint {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR
    };

    enum class TextureFilterModeMin : GLint {
        Nearest = GL_NEAREST,
        NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
        NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
        Linear = GL_LINEAR,
        LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
        LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
    };

    enum class TextureWrapMode : GLint {
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampToBorder = GL_CLAMP_TO_BORDER,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        Repeat = GL_REPEAT,
        MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
    };

    class Texture : public Resource{
    public:
        GLenum target{};
        explicit Texture(GLenum target) : Resource(GL_TEXTURE), target(target){
            glCreateTextures(target, 1, &id);
        }
        ~Texture() override {
            if(id != 0)
                glDeleteTextures(1, &id);
        };
        Texture(Texture&& other)  noexcept : Resource(std::move(other)) {
            target = other.target;
        }

        Texture& operator=(Texture&& other) noexcept {
            if (this == &other)
                return *this;
            target = other.target;
            Resource::operator=(std::move(other));
            return *this;
        }
        void bind(GLuint slot) const {
            glBindTextureUnit(slot, id);
        }

        template<typename T>
        void setParameter(GLenum name, T param) {
            static_assert(std::is_enum<T>::value, "type not supported!");
            setParameter(name, static_cast<typename std::underlying_type<T>::type>(param));
        }
        template<>
        void setParameter<GLfloat>(GLenum name, GLfloat param) {
            glTextureParameterf(id, name, param);
        }
        template<>
        void setParameter<GLint>(GLenum name, GLint param) {
            glTextureParameteri(id, name, param);
        }
        template<>
        void setParameter<const GLint*>(GLenum name, const GLint* param) {
            glTextureParameteriv(id, name, param);
        }
        template<>
        void setParameter<const GLfloat*>(GLenum name, const GLfloat* param) {
            glTextureParameterfv(id, name, param);
        }

        template<typename T>
        void getParameter(GLenum name, T* param) const {
            static_assert(std::is_same<T, void>::value, "type not supported!");
            //static_assert(std::is_enum<T>::value, "type not supported!");
            //setParameter(name, static_cast<typename std::underlying_type<T>::type *>(param));
        }
        template<>
        void getParameter<GLfloat>(GLenum name, GLfloat* param) const {
            glGetTextureParameterfv(id, name, param);
        }
        template<>
        void getParameter<GLint>(GLenum name, GLint* param) const {
            glGetTextureParameteriv(id, name, param);
        }

        template<typename T>
        void getLevelParameter(GLint level, GLenum name, T* param) const {
            static_assert(std::is_same<T, void>::value, "type not supported!");
            //static_assert(std::is_enum<T>::value, "type not supported!");
            //setParameter(name, static_cast<typename std::underlying_type<T>::type *>(param));
        }
        template<>
        void getLevelParameter<GLfloat>(GLint level, GLenum name, GLfloat* param) const {
            glGetTextureLevelParameterfv(id, level, name, param);
        }
        template<>
        void getLevelParameter<GLint>(GLint level, GLenum name, GLint* param) const {
            glGetTextureLevelParameteriv(id, level, name, param);
        }

        GLint getWidth(GLint level = 0) const {
            GLint result;
            getLevelParameter(level, GL_TEXTURE_WIDTH, &result);
            return result;
        }

        GLint getHeight(GLint level = 0) const {
            GLint result;
            getLevelParameter(level, GL_TEXTURE_HEIGHT, &result);
            return result;
        }

        GLint getDepth(GLint level = 0) const {
            GLint result;
            getLevelParameter(level, GL_TEXTURE_DEPTH, &result);
            return result;
        }

        void setFilterMode(TextureFilterModeMin minFilterMode){
            setParameter(GL_TEXTURE_MIN_FILTER, minFilterMode);
        }
        void setFilterMode(TextureFilterModeMag magFilterMode){
            setParameter(GL_TEXTURE_MAG_FILTER, magFilterMode);
        }
        void setFilterMode(TextureFilterModeMin minFilterMode, TextureFilterModeMag magFilterMode){
            setFilterMode(minFilterMode);
            setFilterMode(magFilterMode);
        }
        void setLodBias(GLfloat bias){
            setParameter(GL_TEXTURE_LOD_BIAS, bias);
        }
        void setBorderColor(const GLfloat* color){
            setParameter(GL_TEXTURE_BORDER_COLOR, color);
        }
        void setBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 0.0f){
            GLfloat color[]{r,g,b,a};
            setBorderColor(color);
        }
        void setWrapModeS(TextureWrapMode wrapMode){
            setParameter(GL_TEXTURE_WRAP_S, wrapMode);
        }
        void setWrapModeT(TextureWrapMode wrapMode){
            setParameter(GL_TEXTURE_WRAP_T, wrapMode);
        }
        void setWrapModeR(TextureWrapMode wrapMode){
            setParameter(GL_TEXTURE_WRAP_R, wrapMode);
        }
        void setWrapMode(TextureWrapMode wrapModeS, TextureWrapMode wrapModeT){
            setWrapModeS(wrapModeS);
            setWrapModeT(wrapModeT);
        }
        void setWrapMode(TextureWrapMode wrapModeS, TextureWrapMode wrapModeT, TextureWrapMode wrapModeR){
            setWrapModeS(wrapModeS);
            setWrapModeT(wrapModeT);
            setWrapModeR(wrapModeR);
        }
        void generateMipmaps(){
            glGenerateTextureMipmap(id);
        }

        void setSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels){
            glTextureSubImage1D(id, level, xoffset, width, format, type, pixels);
        }
        void setSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels){
            glTextureSubImage2D(id, level, xoffset, yoffset, width, height, format, type, pixels);
        }
        void setSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels){
            glTextureSubImage3D(id, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
        }

        template<typename T>
        void setSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, const T* pixels){
            static_assert(internal::glconst4type<T>::value != GL_DOUBLE, "invalid type!");
            static_assert(is, "invalid type!");
            setSubImage1D(level, xoffset, width, format, internal::glconst4type<T>::value, pixels);
        }
        template<typename T>
        void setSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, const T* pixels){
            static_assert(internal::glconst4type<T>::value != GL_DOUBLE, "invalid type!");
            setSubImage2D(level, xoffset, yoffset, width, height, format, internal::glconst4type<T>::value, pixels);
        }
        template<typename T>
        void setSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, const T* pixels){
            static_assert(internal::glconst4type<T>::value != GL_DOUBLE, "invalid type!");
            setSubImage3D(level, xoffset, yoffset, zoffset, width, height, depth, format, internal::glconst4type<T>::value, pixels);
        }

        template<typename T>
        void setImage1D(GLint level, GLenum format, const T* pixels){
            setSubImage1D(level, 0, getWidth(level), format, pixels);
        }
        template<typename T>
        void setSubImage2D(GLint level, GLenum format, const T* pixels){
            setSubImage2D(level, 0, 0, getWidth(level), getHeight(level), format, pixels);
        }
        template<typename T>
        void setSubImage3D(GLint level, GLenum format, const T* pixels){
            setSubImage3D(level, 0, 0, 0, getWidth(level), getHeight(level), getDepth(level), format, pixels);
        }

        template<typename T>
        void setImage1D(GLint level, GLenum format, GLenum type, const void* pixels){
            setSubImage1D(level, 0, getWidth(level), format, type, pixels);
        }
        template<typename T>
        void setSubImage2D(GLint level, GLenum format, GLenum type, const void* pixels){
            setSubImage2D(level, 0, 0, getWidth(level), getHeight(level), format, type, pixels);
        }
        template<typename T>
        void setSubImage3D(GLint level, GLenum format, GLenum type, const void* pixels){
            setSubImage3D(level, 0, 0, 0, getWidth(level), getHeight(level), getDepth(level), format, type, pixels);
        }

    };

    inline Texture createTexture2D(GLsizei width, GLsizei height, GLenum format, GLsizei levels) {
        Texture texture(GL_TEXTURE_2D);
        glTextureStorage2D(texture.id, levels, format, width, height);
        return texture;
    }

    inline Texture createTexture2D(GLsizei width, GLsizei height, GLenum format) {
        return createTexture2D(width, height, format, internal::getMipmapLevels({width, height}));
    }

    inline Texture createTexture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei levels) {
        Texture texture(GL_TEXTURE_2D_ARRAY);
        glTextureStorage3D(texture.id, 1, format, width, height, depth);
        return texture;
    }

    inline Texture createTexture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format) {
        return createTexture2DArray(width, height, depth, format,internal::getMipmapLevels({width, height}));
    }

    inline Texture createTexture1D(GLsizei width, GLenum format, GLsizei levels) {
        Texture texture(GL_TEXTURE_1D);
        glTextureStorage1D(texture.id, levels, format, width);
        return texture;
    }

    inline Texture createTexture1D(GLsizei width, GLenum format) {
        return createTexture1D(width, format, internal::getMipmapLevels({width}));
    }


}


