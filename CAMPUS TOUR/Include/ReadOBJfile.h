//Aurthor: Peter Neve
//Version: 1
//Date: 26/08/2021
//Reads .obj file with UV coordinates only

//Future update - allow for non UV .obj files


#ifndef READOFFfile_H
#define READOFFfile_H

#include "Geometry.h"
	/**
	 * @brief Allows program to read .obj files and store in an Object3D
	 *
	 *
	 * @author Peter Neve
	 * @version 01
	 * @date 5/06/2021 Peter Neve, finished OFF file reader
	 * 
	 * @author Peter Neve
	 * @version 02
	 * @date 25/08/2021 Peter Neve, Converted to .obj reader
	 *
	 * @author Peter Neve
	 * @version 03
	 * @date 28/08/2021 Peter Neve, Refactor (seperate definition & implentation)
	 */

	 /**
		* @brief  Read .obj file from specified path, & store in passed object
		*
		*
		* @param char* - fileName
		* @param Object3D* - newObject
		* @return void
		*/
void ReadOBJfile(char* fileName, Object3D* newObject);
	/**
	   * @brief Reads .obj file counting how many of each property their is
	   * dynamically assigning the arrays
	   *
	   *
	   * @param char* - fileName
	   * @param Object3D* - newObject
	   * @return void
	   */
void setArrays(char* fileName, Object3D* newObject);
	/**
	   * @brief  Change index from 1 to 0 base
	   * 
	   * .obj is 1 based while array it 0 based (this compensates)
	   *
	   * @param Object3D* - obj
	   * @return void
	   */
void reIndex(Object3D* obj);
	/**
	   * @brief  free pointer memory
	   *
	   * @param Object3D* - obj
	   * @return void
	   */
void freeObj(Object3D* obj);
	/**
	   * @brief  Print all contents of Object3D
	   *
	   * Can show if data was read correctly
	   *
	   * @param Object3D* - newObj
	   * @return void
	   */
void printObjContent(Object3D* newObj);


	/// max amount of characters to read from file
int const bufferLength = 255;

#endif //READOFFfile_H
