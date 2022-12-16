# EasyLoadingScreen

Unreal Engine plugin for automatic and simplified loading screen creation.

With some shader knowledge you can customize almost any aspect of the loading screen or use example materials as your base.

If you want to support me subscribe to me on [YouTube](https://www.youtube.com/c/FerlinDev) and/or follow my [Twitter](https://twitter.com/FerlinDev)

### Adding Easy Loading Screen to your project 

To add the plugin to your project, download the repository ZIP file.
![image](https://user-images.githubusercontent.com/48950953/208145525-4f270f16-c1a5-42ca-8772-eebd1fb7637b.png)

Add Plugins folder inside your project.
![image](https://user-images.githubusercontent.com/48950953/208145817-255b9795-616d-4005-a588-0745485635ab.png)

Then extract EasyLoadingScreen into the created folder.
![image](https://user-images.githubusercontent.com/48950953/208161365-16dfb953-0e52-4b86-9caa-452ee78ad7ce.png)


After you open your project you will prompted that the following module is missing.

You can either build it by hand or let unreal do it automaticaly by pressing yes.

![image](https://user-images.githubusercontent.com/48950953/208146562-ac7871d4-738d-483b-a8b4-c496f2ab7527.png)

### Open Level Function

To use fade in and fade out animations for loading screen you will need to create a new function inside your Game Instance.

Great tutorial on [Game Instance](https://youtu.be/5w594D3qtLs)

Open FUNCTION_HOLDER inside Plugin's content folder and copy it's content to the Game Instance.
![image](https://user-images.githubusercontent.com/48950953/208149637-953aaf2b-a688-459e-9181-5f0eab7dfada.png)
![image](https://user-images.githubusercontent.com/48950953/208149726-3fc0e7a1-0ec2-490e-b7d2-ad61434129d8.png)
From now when you wish to open the level, just call the created function.
![image](https://user-images.githubusercontent.com/48950953/208150189-05edf798-e157-4e8d-b524-89d44ecac56f.png)

### Transition Animation

Setup Transition Material and Transition Duration inside project settings.
![image](https://user-images.githubusercontent.com/48950953/208151305-3736e3b9-6a87-4dc8-b17b-33d07a38a515.png)

Transition Material is animated using TransitionPhase scalar value.
On loading screen start animated from 0 to 2 and on loading screen end animated from 2 to 0

Background Image + Overlay Material + Loading Sequence will be initialized / removed when the value reaches 1.
![image](https://user-images.githubusercontent.com/48950953/208152088-902cae49-e185-4824-ac6c-6e38fc5f649b.png)

### Background Images

To add background images for your loading screen, go to your project settings and add them to the array.
![image](https://user-images.githubusercontent.com/48950953/208155120-cb22dac2-8776-4517-83a9-f48ab177290b.png)

To handle wide screens you can select Vertical and Horizontal Alignment.

![image](https://user-images.githubusercontent.com/48950953/208155378-ca131bbf-c4c7-4951-aa04-d15cbf4c4514.png)
*if your point of interest is on the left - pick left, if on the top - pick top, etc.*

You can force certain background image to be displayed by changing index in the set background image index.
![image](https://user-images.githubusercontent.com/48950953/208156782-4d3d6580-889c-4472-ad77-66aef2241ac5.png)


### Overlay Material

To add shared look across your loading screen you can add an Overlay Material. This material will projected on top of your background images.
M_ExampleOverlay material is a simple black triangle in the right bottom corner, to separate loading sequence from background images.

![image](https://user-images.githubusercontent.com/48950953/208157428-1451d2a8-6212-4abd-bf1e-18a628d40d37.png)


### Loading Sequence

Last but not least, loading sequence, here you can put target framerate of your sequence, and list of animation "frames".

![image](https://user-images.githubusercontent.com/48950953/208158257-ae0fccf4-2f29-485b-bc59-e69886994434.png)

To help you create loading sequence I created MM_LoadingIcon. Simply create a material instance from it, and edit necessary data.

![image](https://user-images.githubusercontent.com/48950953/208158763-eb36f82d-aded-48bd-805f-864b2dbea723.png)

Horizontal Offset / Vertical Offset -> distance from the screen border.

Screen Percentage -> What percentange of the screen vertical size should the loading icon take.

Texture Height / Width -> Parameters of your loading icon's texture -> used to keep the texture uniformly scaled.

*if your texture is a square you can just make both values 1)*

Right -> Should the texture be placed in the right corner. False = Left Corner.

Top -> Should the texture be placed in the top corner. False = Bottom Corner.

Loading Icon -> Texture for the current animation frame.
