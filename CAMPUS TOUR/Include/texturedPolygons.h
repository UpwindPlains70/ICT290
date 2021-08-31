//  texturedPolygon.h
//  
// 
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef TEXTURE_POLYGON_H
#define TEXTURE_POLYGON_H


//--------------------------------------------------------------------------------------

#include <iostream>
#include <gl/glut.h>
#include <stdio.h>	// should really be using c++, but didn't get time to change
#include <stdlib.h>

//--------------------------------------------------------------------------------------
/**
	 * @brief Header file for the texturedPolygon class
	 *
	 *
	 * @author Shay Leary
	 * @version 01
	 * @date March 2005, Finished
	 *
	 *
	 */
class TexturedPolygons
{
public:

	TexturedPolygons () {}
    virtual ~TexturedPolygons () {Clear();}

	//----------------------------------------------------------------------------------

		/**
		 * @brief  returns texture
		 *
		 * This function returns the index of a texture
		 *
		 * @param  int - texture index
		 * @return GLuint
		 */
	GLuint GetTexture (const int & tempIndex) {return m_texture[tempIndex];}

		/**
		 * @brief  loads a raw image file into memory
		 *
		 *
		 * @param  char* - filepath
		 * @param  int - image width
		 * @param  int - image hieght
		 * @return GLbyte*
		 */
	GLubyte* LoadTexture(char *filename, int imgWidth, int imgHeight);
	
		/**
		 * @brief  set the number of textures to be used
		 *
		 *
		 * @param  int - texture number
		 * @return void
		 */
	void SetTextureCount(const int &textureNo);

		/**
		 * @brief  creates texture and set required values for texture mapping
		 *
		 *
		 * @param  int - texture number
		 * @param  unsigned char* - image
		 * @param  int - image width
		 * @param  int - image height
		 * @return void
		 */
	void CreateTexture(int textureNo, unsigned char* image, int imgWidth, int imgHeight);

		 /**
			 @brief calls function to creates display list to contain image
			 @param int - XYZ      
			 @param int - listNo   
			 @param GLdouble - xImgSize 
			 @param GLdouble - zImgSize 
			 @param GLdouble - xStart   
			 @param GLdouble - yStart   
			 @param GLdouble - zStart   
			 @param GLdouble - xTimes   
			 @param GLdouble - zTimes   
			 @return void
		 **/
	void CreateDisplayList(const int &XYZ, const int &listNo, 
		                   const GLdouble &xImgSize, const GLdouble &zImgSize, 
					       const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
					       const GLdouble &xTimes, const GLdouble &zTimes);

		 /**
			 @brief  used to create display lists where image is larger than world scale on YZ axis

			 @param int - listNo   
			 @param GLdouble - xStart   
			 @param GLdouble - yStart   
			 @param GLdouble - ySize    
			 @param GLdouble - zStart   
			 @param GLdouble - zSize    
			 @param GLdouble - yImgSize 
			 @param GLdouble - zImgSize 
			 @return void
		 **/
	void CreateYtoZWindowList(const int &listNo, const GLdouble &xStart, 
							  const GLdouble &yStart, const GLdouble &ySize, 
							  const GLdouble &zStart, const GLdouble &zSize,
							  const GLdouble &yImgSize, const GLdouble &zImgSize);

		 /**
			 @brief used to create display lists where image is larger than world scale on XY axis

			 @param int - listNo   
			 @param GLdouble - zStart   
			 @param GLdouble - xStart   
			 @param GLdouble - xSize    
			 @param GLdouble - yStart   
			 @param GLdouble - ySize    
			 @param GLdouble - xImgSize 
			 @param GLdouble - yImgSize 
			 @return void
		 **/
	void CreateXtoYWindowList(const int &listNo, const GLdouble &zStart, 
							  const GLdouble &xStart, const GLdouble &xSize, 
							  const GLdouble &yStart, const GLdouble &ySize,
							  const GLdouble &xImgSize, const GLdouble &yImgSize);

		/**
			@brief used to create display lists where image is on an angle

			@param int - listNo      
			@param imageWidth  
			@param imageHeight 
			@param GLdouble - x1          
			@param GLdouble - x2          
			@param GLdouble - x3          
			@param GLdouble - x4          
			@param GLdouble - y1          
			@param GLdouble - y2          
			@param GLdouble - y3          
			@param GLdouble - y4          
			@param GLdouble - z1          
			@param GLdouble - z2          
			@param GLdouble - z3          
			@param GLdouble - z4          
			@param int - smallestX   
			@param int - smallestZ   
			@return void
		**/
	void CreateAngledPolygon(const int &listNo, 
							 const GLdouble &imageWidth, const GLdouble &imageHeight,
							 const GLdouble &x1, const GLdouble &x2, 
							 const GLdouble &x3, const GLdouble &x4,
						     const GLdouble &y1, const GLdouble &y2,
							 const GLdouble &y3, const GLdouble &y4,
							 const GLdouble &z1, const GLdouble &z2,
							 const GLdouble &z3, const GLdouble &z4,
							 const int &smallestX, const int &smallestZ);

private:
	/// pointer to display list
	GLuint *m_texture;

	/// returns image file
	GLubyte* LoadRawImageFile(char* filename, int width, int height);

		 /**
			 @brief clear texture pointer
		 **/
	void Clear ();

		 /**
			 @brief creates display list to contain image on X Z axis
			 @param GLdouble - xImgSize 
			 @param GLdouble - zImgSize 
			 @param GLdouble - xStart   
			 @param GLdouble - yStart   
			 @param GLdouble - zStart   
			 @param GLdouble - xTimes   
			 @param GLdouble - zTimes  
			 @return void
		 **/
	void CreateXtoZTextureList(const GLdouble &xImgSize, const GLdouble &zImgSize, 
					           const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
					           const GLdouble &xTimes, const GLdouble &zTimes);

		 /**
			 @brief creates display list to contain image on X Y axis
			 @param GLdouble - xImgSize 
			 @param GLdouble - yImgSize 
			 @param GLdouble - xStart   
			 @param GLdouble - yStart   
			 @param GLdouble - zStart   
			 @param GLdouble - xTimes   
			 @param GLdouble - yTimes   
			 @param bool - flip     
			 @return void
		 **/
	void CreateXtoYTextureList(const GLdouble &xImgSize, const GLdouble &yImgSize, 
							   const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
							   const GLdouble &xTimes, const GLdouble &yTimes, const bool &flip);

		 /**
			 @brief  creates display list to contain image on Y Z axis
			 @param GLdouble - yImgSize 
			 @param GLdouble - zImgSize 
			 @param GLdouble - xStart   
			 @param GLdouble - yStart   
			 @param GLdouble - zStart   
			 @param GLdouble - yTimes   
			 @param GLdouble - zTimes   
			 @param bool - flip    
			 @return void 
		 **/
	void CreateYtoZTextureList(const GLdouble &yImgSize, const GLdouble &zImgSize, 
							   const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
							   const GLdouble &yTimes, const GLdouble &zTimes, const bool &flip);
	
		 /**
			 @brief determine how images are displayed
			 
			 called from	CreateAngledPolygon

			 @param GLdouble - xzImage1  
			 @param GLdouble - xzImage2  
			 @param GLdouble - xzImage3  
			 @param GLdouble - xzImage4  
			 @param GLdouble - imageSize
			 @return void 
		 **/
	void CreateTextureScale(GLdouble & xzImage1, GLdouble & xzImage2, 
							GLdouble & xzImage3, GLdouble & xzImage4,
							const GLdouble &imageSize);

	//----------------------------------------------------------------------------------

    // 
		/**
			@brief Privatised copy constructor and assignment operator
			@param TexturedPolygons - tp 
			@return TexturedPolygons
		**/
    TexturedPolygons (const TexturedPolygons &tp) {};
		/**
			@brief  operator= overload
			@param  TexturedPolygons - tp 
			@return TexturedPolygons
		**/
    TexturedPolygons &operator = (const TexturedPolygons &tp) {};
};

#endif

//----------------------------------------------------------------------------------