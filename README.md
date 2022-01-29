# MUSI-6106-GroupA
Final Project for Audio Software Engineering, Spring 2022

## Motivation:
- When editing vocals for singers, a variety of plug-ins are often necessary for sound design and music production

## Problem:
- Vocal editing requires knowledge and experience that not all may have yet obtaining better results can be easily achieved with standard plugin processing chains.

## Target Users:
- Amateur users who may not know what effects or parameters to use and want a quick and easy fix that sounds good (i.e., clear, reverberant, in-tune, saturated, etc.), users who want quick final touches on existing processing
- Our main target audiences include amateur mixing engineers, mastering engineers, music producers, sound designers, and audio editors. We will focus specifically on applications involving sung vocals, rather than voice-over effects (i.e. podcasts). 
- The final plugin will also have an advanced user setting for us to easily prototype and if users want finer configuration.

## Goal:
- Create an “all-in-one” vocal plugin that includes any effect one may need to apply to a vocal track all within a single application. Real-time plug-in that can be rendered both online/offline. Includes audio presets for additional ease of use.

## Use Cases:
- Karaoke (set once for the machine/karaoke plugin, and then leave it), Streaming music performances, hobby production
functionality from user point of view and how it differentiates from similar products
- Single knob/parameter with presets for the user to adjust, rather than a potentially overwhelming set of options example
- *nice to have but will do for our own prototyping* - open up the application for more advanced users to customize individual parameters
![alt text](https://github.com/johnnymac647/MUSI-6106-GroupA/blob/[main]/imgs/flowchart_dsp.jpg?raw=true)

## Description of Functionality:
- UI:
  - All
    - Output meter
  - Default UI
    - 1 knob (dry/wet)
    - 2 switches for the audio presets below
  - Advanced User (for users & us to easily prototype)
- Effects:
  - Gate
  - Compression
  - De-esser
  - EQ
  - Saturation
  - Singing only:
    - Delay
    - Impulse Reverb
  - Output meter
- Audio presets for additional user ease of use
  - Voiceover vs singing -> Treble vs bass
  - Other options we may incorporate later:
    - Various styles, e.g. lofi, radio, natural, modern

## Work Packages:
- JUCE: GUI, DSP packages
- (Potentially) Eigen for linear algebra

## Milestones:
- Milestone 1: Fully configurable parameters for advanced users (est. 03/07)
- Milestone 2: Single knob with preset selector for amateur users (est. 04/14)

## Timeline:
- 01/10-01/31: Ideas brainstorm, getting used to C++ & JUCE
- 01/31-02/07: Study best practices on how to implement the whole pipeline
- 02/07-02/14: Working on the skeleton code abstract class (general code to incorporate all empty FX classes) & UI knobs / switches for advanced/amateur user setting & linking to the audio effects (decide on what parameters to have)
- 02/14-02/21: Finish skeleton code for FX & UI classes
- 02/21-02/28: Implement baseline set of individual features in isolation
- 02/28-03/07: Implement baseline set of individual features in isolation
- 03/07-03/14: Finish implementing & testing baseline set of individual features in isolation
- 03/14-03/21: Creating presets for voiceover vs singing
- 03/21-03/28: Creating presets for bass vs treble (voiceover), bass vs treble (singing)
- 03/28-04/11: Testing / buffer time
- 04/11-04/18: Testing / buffer time
- 04/18-04/25: Finish

## Assignments:
- Refer to [Trello Board](https://trello.com/invite/b/7HRsFj9L/90a86310a9f8ad93f25989c4a3787caf/musi-6106-ase-group-a)
- Group Members:
  - Alison: Gate/De-esser, UI and audio class linking, Preset Parameters
  - John: Delay/Reverb, Project Management/Trello Manager, UX Design
  - Sile: EQ/Compression, Developer
  - Nitin: Compression, UX Design, Developer
  - Mike: Distortion, Developer
