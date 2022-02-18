/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2016-2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::functionObjects::textFields

\*---------------------------------------------------------------------------*/

#ifndef functionObjects_textFields_H
#define functionObjects_textFields_H

#include <sys/stat.h>
#include "fvCFD.H"
#include "fvMeshFunctionObject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

namespace functionObjects
{

/*---------------------------------------------------------------------------*\
                          Class textFields Declaration
\*---------------------------------------------------------------------------*/

class textFields
:
public fvMeshFunctionObject
{

private:

    // Private Data

        //- Current time of the simulation
        const Time& runTime_;

        //- Name of the directory
        word folder_;

        //- Name of velocity field
        word UName_;

        //- Name of alpha field
        word alphaName_;

        //- Reference to velocity field
        const volVectorField& U_;

        //- Reference to alpha field
        const volScalarField& alpha_;

    // Private Member Functions

        void writeCUA
        (
            std::ofstream&,
            const vectorField&,
            const vectorField&,
            const scalarField&
        );

        void parRunMaster(std::ofstream&);

        void parRunSlave();

public:

    //- Runtime type information
    TypeName("textFields");

    // Constructors

        //- Construct from Time and dictionary
        textFields
        (
            const word& name,
            const Time& runTime,
            const dictionary& dict
        );

        //- No copy construct
        textFields(const textFields&) = delete;

        //- No copy assignment
        void operator=(const textFields&) = delete;

    //- Destructor

        virtual ~textFields() = default;

    // Member Functions

        //- Read the textFields data
        virtual bool read(const dictionary&);

        //- Execute, currently does nothing
        virtual bool execute();

        //- Calculate the textFields and write
        virtual bool write();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace functionObjects
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
