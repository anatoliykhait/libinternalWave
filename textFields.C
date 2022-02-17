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

\*---------------------------------------------------------------------------*/

#include "addToRunTimeSelectionTable.H"
#include "textFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace functionObjects
{
    defineTypeNameAndDebug(textFields, 0);
    addToRunTimeSelectionTable(functionObject, textFields, dictionary);
}
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::functionObjects::textFields::textFields
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    fvMeshFunctionObject(name, runTime, dict),
    runTime_(runTime),
    UName_(dict.lookup("U")),
    alphaName_(dict.lookup("alpha")),
    U_(lookupObject<volVectorField>(UName_)),
    alpha_(lookupObject<volScalarField>(alphaName_))
{
    read(dict);

    folder_ = word(dict.lookup("folder"));

    if (UPstream::master())
    {
        struct stat st;
        if (stat(folder_.data(), &st) == -1)
        {
            // "0777" == -rwxrwxrwx
            mkdir(folder_.data(), 0777);
        }
        else
        {
            Info << "Folder " << folder_ << " exists ;"
                 << " continue writing in this folder" << endl;
        }
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::functionObjects::textFields::read(const dictionary& dict)
{
    fvMeshFunctionObject::read(dict);

    return true;
}


bool Foam::functionObjects::textFields::execute()
{
    // Info << "This is EXECUTE" << endl;

    // int a;
    // forAll(mesh_.cells(),cellI)
    // {
    //     ++a;
    // }

    // Info << a << endl;

    return true;
}


bool Foam::functionObjects::textFields::write()
{
    std::ofstream filefields;
    filefields.open(
               ("./" + folder_ + "/time_" + runTime_.timeName()).data(),
               std::ios::out);

    filefields << "# x   y   z   u   v   w   alpha" 
               << "\n";

    if (Pstream::parRun())
    {

    }
    else
    {
        
    }

    filefields.close();

    return true;
}


// ************************************************************************* //
