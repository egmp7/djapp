/*
  ==============================================================================

    DeckGUI.h
    Created: 12 Jan 2023 7:05:21pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>
//Models
#include "SliderModel.h"
// controllers
#include "Crossfader.h"
#include "DJAudioPlayer.h"
// child components
#include "WaveformDisplay.h"
#include "TimeTracker.h"
#include "DeckAnimation.h"
#include "Volume.h"
#include "Speed.h"
// lookAndFeel
#include "FadersLookAndFeel.h"

using namespace juce;
using namespace std;

//==============================================================================

class DeckGUI  : public Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer,
                 public DragAndDropTarget
{
public:
    DeckGUI(DJAudioPlayer* player,
            Crossfader* _crossfader,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse,
            bool _mirror);
    ~DeckGUI() override;

    
    void paint (juce::Graphics&) override;
    void resized() override;
    
//==============================================================================
    
    /**Implementation for  Button when clicked
     @param button button clicked */
    void buttonClicked(Button *) override;
    /**Implementation for Slider when user drags
     @param slider slider moved*/
    void sliderValueChanged (Slider *slider) override;
    /**Checks drag and drop  system files when entering the component rectangle
     @param &files an array of files  selected when dragging
     @returns true when item is inside the component*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    /**Loads system audio files to the application
     @param &files an array of files  selected when dragging
     @param x coordenate relative to the component,
     @param y coordenate relative to the component*/
    void filesDropped (const StringArray &files, int x, int y) override;
    /**Checks for drag and drop object sources
     @param &dragSourceDetails contains file names
     @returns true when item is inside the component */
    bool isInterestedInDragSource (const SourceDetails &dragSourceDetails) override;
    /**Loads audio files to the application
     @param &dragSourceDetails contains file names*/
    void itemDropped (const SourceDetails &dragSourceDetails) override;
    /**Calls the waveform load function
     @param file loading file*/
    void loadWaveform(URL file);
    /**Updates time tracke with a setterr**/
    void updateTimeTracker();
    /**Callback function to run setter **/
    void timerCallback() override;
    /**Get the slider meta data to draw custom volume thumbnails**/
    SliderModel getVolSliderModel();
    /**Get the slider meta data to draw custom speed thumbnails**/
    SliderModel getSpeedSliderModel();
    
    /**Get the slider value of the volume and speed components
     @returns volume and speed float values**/
    map<string,float> getSliderValues();

private:
    
    // Controllers
    DJAudioPlayer* player;
    Crossfader* crossfader;
        
    // GUI Components
    ImageButton playPauseButton{"Play/Pause"};
    ImageButton cueButton{"CUE"};
    ImageButton loadButton{"LOAD"};
    
    Volume volume;
    Speed speed;
    
    Slider volSlider;
    Slider speedSlider;
    
    WaveformDisplay waveformDisplay;
    TimeTracker timeTracker;
    DeckAnimation deckAnimation {player};
    
    //Utilities
    FadersLookAndFeel fadersLookAndFeel{FaderType::vertical};
    FileChooser fChooser{"Select a file..."};
    bool mirror;
    float cue;
    int cueCounter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
