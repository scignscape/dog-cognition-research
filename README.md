# dog-cognition-research

This repository contains code and data developed in conjunction with a study on canine communication with an emphasis on observations of dogs who have learned to use Augmentative and Alternative Communication (AAC) buttons.  Currently the published material within this project is contained in Chapter 23 of the book on "_Industry 4.0_" cited below.  For simplicity, code and information discussed in others chapters of this book are included in the current repository as well.

The data set is one of a series of data sets which are under development and/or have been curated in conjunction with published research on linguistics and technology.  Several of these data sets are reproduced in the current repository.  Note that the additional data sets are devoted to "natural" human language as it is usually understood, not to "animal" communication.

The overall purpose of this collection is to connect Cognitive Linguistics with certain computational methods often associated with Natural Language Processing, corpus-based analysis, and mathematical approaches to language theory, including "non-human" language such as computer code (Software Language Engineering).  Published work or data-set analysis papers included here generally adopt Cognitive Linguistics methods (especially Cognitive Grammar) but this perspective is augmented with language-related software, with the goal being to augment the semi-formal cognitive-humanistic perspectives with some more systematic/statitical methodology.

Information about the overall data-set collection is provided later in this file.

# Introduction

---
**What is included in the "dog-cognition" data set**

We are currently analyzing video feeds published on social media following the work of two pioneers in dog-communication research via AAC devices, name Christina Hunger and her dog Stella (a Catahoula/Blue Heeler mix), and Alexis Devine with her dog Bunny (a Sheepadoodle).  

Due to copyright and space concerns we do not currently include the actual videos which are available on YouTube, Instagram, or TikTok.  We intend the data set published in this location to include summaries and annotation files of the video collection, as well as computer code for reviewing and/or visualizing the annotations.  Users who would like to view the entire video set on their own without taking the trouble to download this content themselves are invited to contact us; we'll try to share this material if possible.  Our code for _downloading_ the videos is open-source and can be shared, but it is not particularly well-documented at this point.  Different social-media platforms have different protocols for downloading content "en masse" (see below for more information about this project's overall code base).

Currently we are working with about 22GB of video files, including 1861 from Bunny (917 Instagram, 808 TikTok, 136 YouTube) and 239 from Stella (193 Instagram, 30 TikTok, 16 YouTube).  For an introduction to dogs' AAC buttons, readers are encouraged to consult _How Stella Learned to Talk_ by Christina Hunger (William Morrow, 2021).  With reference to this data set specifically, we have published a chapter-length analysis focusing on Stella (Bunny to a lesser extent) as Chapter 23 of the compilation _AI, IoT, Big Data and Cloud Computing for Industry 4.0_ (Springer, forthcoming), titled "`The Missing Links Between Computer and Human Languages: Animal Cognition
and Robotics`".  Nathaniel Christen, the lead author on that chapter (I'm the one compiling this data set) contributed Chapters 20-24 of that volume (expected Spring 2023), chapters which address a variety of topics in linguistics and technology (focusing on programming-language implementation,  database engineering, Geographic Information Systems, and Computer Vision, as well as linguistics).  The connection between linguistics and these various computing topics may seem tangential, but they are backed up arguments further developing work I published in a recent book (_Innovative Data Integration and Conceptual Space Modeling for COVID, Cancer, and Cardiac Care_, Elsevier 2022, particularly Chapters 6 and 9).  For those interested a "prelimary" (or quote-unquote preliminary) version of the 2023 book are included with this data set, including the specific chapter on "talking dogs" and the following chapter about "Neo-Davidsonian Procedural Semantics" which extends some of its arguments.

---

## Computer Code for the Data Set ##
We have implemented fairly extensive code base in conjunction with these data sets, but in keeping with the maxim that perfecting code takes much longer than text, a lot of the code is still provisional and poorly documented.  Currently we are keeping the code at the repo `https://github.com/ScignScape/ntxh`.  The README there points readers toward the `ctg` branch for the main data set material, but code specifically related to *this* (dog-cognition) repository is on the `ctg-temp` branch.  We mention this work to clarify the source of code discussed in the _Industry 4.0_ chapters, including procedures for downloading social-media videos, but again we simply have not had time yet to properly curate this code for a public audience.  For the time being we will provide a brief outline of the relevant components, and invite those curious about the overall project to ask about specific features (or to browse the most recent code, assuming one does not object to its work-in-process flaws).

With that preamble out of the way, the following is a brief discussion of different parts of the code base mentioned in Section 5 (chapters 20-24) of the _Industry 4.0_ text referenced earlier.

### Video Annotations ###

Probably the most directly relevant material to the present data set is code for viewing and annotating videos.  The video annotations themselves are composed with a special-purpose format we call `NTXH` (this format actually combines several domain-specific languages each contributing one letter to the "`NTXH`" moniker).  The annotations are read by a special-purpose video player which converts them into graphics overlaid on the video content, offering a wider range of diagram and text-styling options than is possible with conventional video-annotation formatics (which usually can do little more than add short text segments).  The compbined video-plus-annotation feed can then be captured to create a composite video, which could then be accessed by any normal video player (so that the annotations become "baked in" superimposed on the video proper).

Similar technology can be used for creating other kind of videos, such live application demonstrations or captures from Virtual Reality, Panoramic Photography, or Street View tours.  For example, virtual walks through buildings or urban locales could be captured as 360-camera tours and converted to video using the code included here.  We have created several videos showing demo applications which describe some of these features.  These videos are not hosted in this repository directly, because of file-size limitations, but may be accessed through the link (current as of early 2023) [on Geographic Information Systems and Digital Map Clients](http://lingtechsys.com/videos/dhax-composite.mkv), [on Virtual Tours and Panoramic Photography](http://lingtechsys.com/videos/qmt-composite.mkv), and [on Image Processing](http://lingtechsys.com/videos/xcsd-composite.mkv) -- but do check their file size before downloading if you want to avoid relatively large range (in the 10s-100s MBs).  

### Image Processing ###

Chapter 22 of the _Industry 4.0_ book presented a novel image format which is optimized for Computer Vision applications in a database context.  Code for creating, viewing, and analyzing images in this format will be recreated here in conjunction the five chapters in Section 5.  Currently we are migrating the code from another repository to the `wip` branch of this archive, so that branch will be more current than `main`. 




