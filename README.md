# Audio-Programming-Module

Contained within this repo is a plugin for Unreal Engine 5.2 which contains all of the content created for use with the Dynamic Audio System that I created.
This includes:
 - Audio Tracks
 - Trigger Box Actor
 - Blueprint Function Library

This repo also includes a demonstration video of the project working, as well as images of the blueprint functions.

If you wish to implement the plugin for youself, please follow the instructions below within Unreal Engine 5.2.

# Implementation Instructions
First, ensure that you are using Unreal Engine 5.2, then download the repo and move it to the plugins folder of your project.

Next, place the sound trigger actor wherever you desire within the world. You may designate this trigger as a “Major Area”, doing so means that the game will default to the track set within this actor if the player is not inside any other triggers. 
After this, add the Metasound source to your desired character blueprint as an audio component during the On Play event. You can also use this event to activate the mixer and set any parameters. 
Finally, timplement an On Overlap Begin event on your chosen character blueprint. When doing so, you must call the “On Overlap Begin” function within the blueprint library, this will handle all of the logic in switching the tracks depending on the overlap, the same goes for calling the “On Overlap End” after the On Overlap End event.
Once these functions are called and the correct parameters are passed in, the system will work.
If you wish to trigger the events in the mixer sound source themselves, you must use the audio component and call “Execute Trigger Parameter”. The triggers you can execute are as follows:
-	Play Main Track – Will play the main track that is passed in
-	Fade In – Will fade in the second track
-	Fade Out – Will fade out the second track
-	Stop Tracks – Will stop all tracks playing within that audio component
