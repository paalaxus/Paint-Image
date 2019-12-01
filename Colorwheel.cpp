/** PAA KOFI BOAFO */
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include "CImg.h"

using namespace std; 
using namespace cimg_library;
 	
bool isValidPosition(int x, int y,int width,int height,int r,int g,int b,CImg <unsigned char> &workimage)
   {
	   
	
	  if( 0<=x and x<width and 0 <= y  && y < height and workimage(x,y,0,0)==r and workimage(x,y,0,1)==g and workimage(x,y,0,2)==b )
	 {
			return true;
      }
      else 
     return false;
     
}

 void fill(CImg<unsigned char>& workimage,CImg <unsigned char>& wheel, int x,int y,int w,int z,int height,int width,int r,int g,int b)
{
	//create a queue and enqueue starting pixel
	queue<pair<int,int> >q;
	q.push(make_pair(x,y));
	
	//initial pixel color (white)
	int rr=workimage(x,y,0,0);
	int gg=workimage(x,y,0,1);
	int bb=workimage(x,y,0,2);
	//get target pixel (all adjacent white pixels will be changed to this)
	
	int rrr =wheel(w,z,0,0);
	int ggg=wheel(w,z,0,1);
	int bbb=wheel(w,z,0,2);
	
	workimage(x,y,0,0)=rrr;
	workimage(x,y,0,1)=ggg;
	workimage(x,y,0,2)=bbb;
	 
	 bool **visited;
	visited = new bool*[width];
      for (int j=0;j<width;j++)
         {
			 visited[j]= new bool [height];
			 for (int i=0;i<height;i++)
			 {
				visited[j][i]=false;
		 }
		 }
		 visited[x][y]=true;
	//run till queue isnt empty
	while(!q.empty())
	{
		//pop front node from queue and process
		pair<int, int> node = q.front();
		q.pop();
		
		//(x,y) represents pixel position from mouse click
		 x=node.first, y=node.second;
				 
		//process adjacent pixels of current and enqueue 
	
		//col represents the horizontal (x-axis)
			//row represents the vertical (y-axis)
			// rr gg bb represent the initial values of the first chosen pixel
			
			if(isValidPosition(x+1,y,width,height,rr,gg,bb,workimage)  and !visited[x+1][y])
			{
				workimage(x+1,y,0,0)=rrr;
				workimage(x+1,y,0,1)=ggg;
				workimage(x+1,y,0,2)=bbb;
				
				visited[x+1][y]=true;
				
				q.push(make_pair(x+1,y));
				
			}
			
			if(isValidPosition(x-1,y,width,height,rr,gg,bb,workimage)  and !visited[x-1][y])
			{
				workimage(x-1,y,0,0)=rrr;
				workimage(x-1,y,0,1)=ggg;
				workimage(x-1,y,0,2)=bbb;
				
				visited[x-1][y]=true;
				
				q.push(make_pair(x-1,y));
				
			}
			if(isValidPosition(x,y+1,width,height,rr,gg,bb,workimage)  and !visited[x][y+1])
			{
				workimage(x,y+1,0,0)=rrr;
				workimage(x,y+1,0,1)=ggg;
				workimage(x,y+1,0,2)=bbb;
				
				visited[x][y+1]=true;
				
				q.push(make_pair(x,y+1));
				
			}
			if(isValidPosition(x,y-1,width,height,rr,gg,bb,workimage)  and !visited[x][y-1])
			{
				workimage(x,y-1,0,0)=rrr;
				workimage(x,y-1,0,1)=ggg;
				workimage(x,y-1,0,2)=bbb;
				
				visited[x][y-1]=true;
				
				q.push(make_pair(x,y-1));
				
			}
		

	}
			
}
				
 
int main(int argc, char *argv[])
{
	string pic=""; 
	string wheelchoice="";
	string savefile="";
	cout<<"Enter picture to color"<<endl;
	cin>>pic; 
	cout<<"Choose wheel to use"<<endl; 
	cin>>wheelchoice;
    CImg<unsigned char> workimage(pic.c_str()); //user entered work image
	CImg<unsigned char> wheel(wheelchoice.c_str());
	
	int height = workimage.height();
	int width = workimage.width();
		
	CImgDisplay mainwindow(workimage,"Test Image"); //show image
	CImgDisplay subwindow(wheel,"Color Wheel"); 
	cout<<"Click start position "<<endl;
	
   					
		while(  !subwindow.is_closed() )
		{ 		subwindow.wait();
									
					
				while (subwindow.button() and subwindow.mouse_y()>=0 and subwindow.mouse_x()>=0)
				{ 

			
					const int w = subwindow.mouse_x();
					const int z= subwindow.mouse_y();
					cout<<"Clicked w: "<<w<<" z: "<<z<<endl;
					
					int rrr =wheel(w,z,0,0);
					int ggg=wheel(w,z,0,1);
					int bbb=wheel(w,z,0,2);
					
			
				 while (!mainwindow.is_closed())
				{
						mainwindow.wait();
						
						if(mainwindow.button() and mainwindow.mouse_y()>=0 and mainwindow.mouse_x()>=0)
						{
							const int x= mainwindow.mouse_x();
							const int y=mainwindow.mouse_y();
							cout<<"clicked x: "<<x<<" y: "<<y<<endl;
						
							fill(workimage,wheel,x,y,w,z,height,width,rrr,ggg,bbb);
							
							mainwindow.display(workimage);
							break;
						}
						mainwindow.flush();
					}
				
					subwindow.display(wheel);	
					
				}
			
				
				subwindow.flush();	
		}
		//ask if user wants to save
		
				int save =cimg::dialog("Save","Do you want to save?","Yes","No");
				if (save==0)
				{
					cin>>savefile;
					workimage.save(savefile.c_str());
				}
				else
				return 0;
				
				
	
				
}
	
