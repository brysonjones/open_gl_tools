#include "graphics.hpp"

namespace graphics {

    // function generates the list of vertex values for a 6 value vertex shader
    // that specifies x, y, z location and r, g, b color
    std::vector<float> generateVertices(std::vector<int> centerPos, 
                                        std::vector<int> dims, 
                                        std::vector<int> map_size,
                                        int color){
                                        // dims - <width, height, depth>

        float xLoc = (float) centerPos[0] / map_size[0];
        float yLoc = (float) centerPos[1] / map_size[1];
        float zLoc = 0.0f;
        std::vector<float> xOffset = {(float)(dims[0]/2)/map_size[0], 
                                      -(float)(dims[0]/2)/map_size[0], 
                                      (float)(dims[0]/2)/map_size[0],  
                                      -(float)(dims[0]/2)/map_size[0], 
                                      (float)(dims[0]/2)/map_size[0], 
                                      -(float)(dims[0]/2)/map_size[0]}; 
        std::vector<float> yOffset = {-(float)(dims[1]/2)/map_size[1], 
                                      -(float)(dims[1]/2)/map_size[1],   
                                      (float)(dims[1]/2)/map_size[1], 
                                      -(float)(dims[1]/2)/map_size[1],   
                                      (float)(dims[1]/2)/map_size[1],  
                                      (float)(dims[1]/2)/map_size[1]};
        std::vector<float> zOffset = {0.0f};
        std::vector<float> vertices(36, 0);
        for (int i=0; i<6; i++){
            vertices[0 + i*6] = xLoc + xOffset[i];
            vertices[1 + i*6] = yLoc + yOffset[i];
            vertices[2 + i*6] = zLoc + zOffset[i];
            if (color == RED){
                vertices[3 + i*6] = 1.0;
            } else if (color == GREEN){
                vertices[4 + i*6] = 1.0;
            } else if (color == BLUE){
                vertices[5 + i*6] = 1.0;
            }
        }
        return vertices;
    }
}