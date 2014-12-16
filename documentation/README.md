Professor Allen's Assignment:

> Dear Bioninfors,

> I am putting in writing the steps and criteria that you should follow for developing your final project including the document on your project that you will submit on the project and for developing the presentation you will give on your project during the final exam period for our course.

> 1. [x] An appropiate, informative project name.
> 2. [x] An introductory paragraph describing your project.
> 3. [x] A detailed description of the interface for your project.
> 4. [x] Step by step description of the organization of your project from design to final product (code).
> 5. [ ] Specs for each step in 4.
> 6. [ ] The division of labor among the project team members.
> 7. [ ] Any special coding features you use/develop.
> 8. [ ] A graphic of your code organization.
> 9. [x] Testing results.
> 10. [x] Code.

> In thinking about your actual final presentation, all project team members should participate in the presentation in an integrated fashion.  Speak clearly and loudly enough.  If appropriate and if it will enhance understanding for the audience, use artifacts (PP, diagrams, videos, activities) in addition to demonstrating code during your presentation.

> Rich



## Projekt Name
Full name: FAST-HawkXaNia
Abbreviation: FAST-HXV

## A Moste Excellente Introductory Paragraph

The purpose of this software is to run the Fasta Algorithm across two strings which are given as input, either via the command line or from a file. It has various settings that you can change at runtime via command-line flags, such as the match-tuple size, the "wonklessness" (technical term), and the number of results returned.


## As a Description of the Interface

FAST-HawkXaNia is a command-line tool for POSIX-compliant systems. It takes input either from the command-line or via an input file, with a format as specified in the README.

It takes the input, processes it, and prints the results to STDOUT.


## On the Organization of our Moste Excellente Projekt

We began our project by implementing the basic FASTA algorithm to print out a dot matrix of matches. We then expanded that to include classes to hold a match, a combination of matches (an alignment), and a catalog of all the matches. Next we populated the catalog with all match combination possibilities, and then edited that catalog removing the different types of invalid alignments (ones with repeating x or y coordinates, and ones with reverse diagonals). Finally we implemented a scoring system that has the ability for the user to choose how much deviation from the ideal mean line is allowed, and then printed the various information out to the user.

## The Mysterious Specs


## On the Division of Labour

This was Xandra's idea, originally. Virginia joined the project first, followed quickly by Hawken. Xandra wrote the initial draft of the basic FASTA algorithm

## On our Hidden Coding Features


## A Singular Graphique, Representing the Organization of our Code


## Proof that our Moste Excellente Program shall Run


## The Code for the Projekt
Included elsewhere.

Run "cat ./**/*.cpp ./**/*.h" in a terminal, without quotes, in the project directory.
