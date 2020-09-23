# 3GC3_Final_Project

This culmulative group project was designed and developed for a computer graphics undergraduate course at McMaster University. To be able to compile and run the project, it is necessary to set up OpenGL and freeglut. To compile the project, use the command "make" while in the main directory. (Inside the Project Folder).

## Project Description
A cooking game that takes place in a 3-D simulating kitchen, where the player selects a recipe and must interact with
 ingredient objects and tool objects and follow the instructions given to create the dish.

<img src="/jpg/gameplay.png" alt="Kitten"
	title="A cute kitten" width="400" height="350" />
	
	
#### This is a short demo:	
<img src="/jpg/demo-steak.gif" alt="demo"
	title="cooking a steak" width="400" height="350" />

 
## Interface
| Command  | Description  |
|---|---|
| q  | quit  |
| up arrow  | move camera to look up  |
| down arrow  | move camera to look down  |
| left arrow  | move camera to look left |
| right arrow  | move camera to look right  |
| left-click  | To select an ingredient or tool. The selected object moves along with the mouse until the next left click.  |   
| right-click  | To use the knife tool. Place the knife over an ingredient and then right click on knife to cut the ingredient into pieces.  |


     
## Project References: 

renderBitmapString:
 - referenced from https://www.programming-techniques.com/2012/05/font-rendering-in-glut-using-bitmap-fonts-with-sample-example.html

Handler, Interaction Handler
- referenced from course tutorial material (tutorial 6)

knife: 
 - created by sepandj
 - downloaded from turbosquid.com
 - https://www.turbosquid.com/FullPreview/Index.cfm/ID/1387505
 

kitchen table:
- created by ultraplex
- downloaded from turbosquid.com 
- https://www.turbosquid.com/FullPreview/Index.cfm/ID/740604
 
 
banana:
- created by rstecca
- downloaded from turbosquid.com
- https://www.turbosquid.com/FullPreview/Index.cfm/ID/682101
 
 
steak: 
- created by Vinrax 
- downloaded from turbosquid.com 
- https://www.turbosquid.com/3d-models/free-blend-model-low-poly-food/740569
 
 
 
potato 
- created by printable_models 
- downloaded from free3d.com 
- https://free3d.com/3d-model/potato-v1--610124.html


pan:
- created by printable_models
- downloaded from free3d.com
- https://free3d.com/3d-model/-12-frying-pan-v2--434551.html



mango: 
- created by Francesco Coldesina
- downloaded from sketchfab.com
- https://sketchfab.com/3d-models/mango-low-6017630990da4e57a7e4d016cdfb0427


tomato: 
- created by printable_models
- downloaded from free3d.com
- https://free3d.com/3d-model/tomatobeefsteak-v1--513542.html


onion: 
- created by printable_models
- downloaded from free3d.com
- https://free3d.com/3d-model/onion-v1--98055.html


pot: 
- created by nmaison88
- downloaded from free3d.com
- https://free3d.com/3d-model/cooking-pot-33147.html


cutTomato: 
- created by storque12
- downloaded from free3d.com
- https://free3d.com/3d-model/tomatoes-45254.html


cutPotato: 
- downloaded raw model from tomato and image texture from google.com 
- https://www.google.com/url?sa=i&source=images&cd=&ved=2ahUKEwiX6ZPWxOjlAhUUrZ4KHQ2uDWsQjRx6BAgBEAQ&url=https%3A%2F%2Fwww.mr-fruity.co.uk%2Fproduct%2Fbaking-potatoes-medium-50-count%2F&psig=AOvVaw10b_s3-3znQVl2TTR4-v01&ust=1573780835419274



cutOnion: 
- downloaded raw model from tomato and image texture from google.com 
- https://www.google.com/url?sa=i&source=images&cd=&ved=2ahUKEwismJuDxejlAhWKsZ4KHfpQB9kQjRx6BAgBEAQ&url=https%3A%2F%2Fwww.123rf.com%2Fphoto_36647461_purple-onion-is-thin-split-on-lightbox-it-show-texture-are-beautiful-.html&psig=AOvVaw3J_lU6epvaTppI62P0b7fH&ust=1573780937979180


cutMango: 
- downloaded raw model from tomato and image texture from google.com 
- https://www.google.com/imgres?imgurl=https%3A%2F%2Fimagesvc.meredithcorp.io%2Fv3%2Fmm%2Fimage%3Furl%3Dhttps%253A%252F%252Fstatic.onecms.io%252Fwp-content%252Fuploads%252Fsites%252F37%252F2015%252F06%252F15211346%252F100342440.jpg%26q%3D85&imgrefurl=https%3A%2F%2Fwww.bhg.com%2Frecipes%2Fhow-to%2Fcooking-basics%2Fhow-to-peel-mango%2F&docid=V3laVXaVeKwCFM&tbnid=Kk5OFFchL4Md-M%3A&vet=10ahUKEwjXmO2IxejlAhWniOAKHRUUCdAQMwiiASgXMBc..i&w=550&h=550&hl=en-CA&bih=789&biw=1440&q=mango&ved=0ahUKEwjXmO2IxejlAhWniOAKHRUUCdAQMwiiASgXMBc&iact=mrc&uact=8
- https://www.google.com/url?sa=i&source=images&cd=&ved=2ahUKEwjsuIS6xejlAhUFvZ4KHS3VCMIQjRx6BAgBEAQ&url=https%3A%2F%2Fwww.fruttaweb.com%2Ffrutta-e-verdura-esotica%2F107-mango-tommy-atkins.html&psig=AOvVaw1-sDq9sdj5pKp1F-0w2qWJ&ust=1573781060302885

cutBanana: 
- downloaded image texture from google.com
- https://www.google.com/url?sa=i&source=images&cd=&ved=2ahUKEwipl8eSw-jlAhUEDKwKHUUED-8QjRx6BAgBEAQ&url=https%3A%2F%2Fucdintegrativemedicine.com%2F2017%2F02%2Fbeautiful-bounty-banana-bread%2Fsliced-banana%2F&psig=AOvVaw2kGof4GL3F3RNZUj_qrdNs&ust=1573780421379142

cookedBeef: 
- created by YurkYurk
- downloaded from cgtrader.com
- https://www.cgtrader.com/free-3d-models/food/miscellaneous/food-set

bowl 
- created by Neax 24 Studio 
- downloaded from turobosquid.com 
- https://www.turbosquid.com/3d-models/bowl-jas-cheetah3d-obj-free/1087707

spoon 
- medusa86 
- downloaded from turbosquid.com 
- https://www.turbosquid.com/FullPreview/Index.cfm/ID/981350



obj loader:
- https://www.raywenderlich.com/2604-how-to-export-blender-models-to-opengl-es-part-1-3
