//#version 430 core
//
//out vec4 fragmentColor;
//in vec4 color;
//
//void main()	{
//    fragmentColor = color;
//    fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
//}

#version 430 core

out vec4 fragmentColor;
in vec4 color;

void main()	{
    fragmentColor = color;
}