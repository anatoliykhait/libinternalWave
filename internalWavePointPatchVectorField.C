/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
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

#include "internalWavePointPatchVectorField.H"
#include "pointPatchFields.H"
#include "addToRunTimeSelectionTable.H"
#include "Time.H"
#include "polyMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

internalWavePointPatchVectorField::
internalWavePointPatchVectorField
(
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF
)
:
    fixedValuePointPatchField<vector>(p, iF),
    amplitude_(0),
    omega_(0),
    phase_(0)
{}


internalWavePointPatchVectorField::
internalWavePointPatchVectorField
(
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF,
    const dictionary& dict
)
:
    fixedValuePointPatchField<vector>(p, iF, dict),
    amplitude_(dict.lookup("amplitude")),
    omega_(dict.get<scalar>("omega")),
    phase_(dict.get<scalar>("phase"))
{
    if (!dict.found("value"))
    {
        updateCoeffs();
    }
}


internalWavePointPatchVectorField::
internalWavePointPatchVectorField
(
    const internalWavePointPatchVectorField& ptf,
    const pointPatch& p,
    const DimensionedField<vector, pointMesh>& iF,
    const pointPatchFieldMapper& mapper
)
:
    fixedValuePointPatchField<vector>(ptf, p, iF, mapper),
    amplitude_(ptf.amplitude_),
    omega_(ptf.omega_),
    phase_(ptf.phase_)
{}


internalWavePointPatchVectorField::
internalWavePointPatchVectorField
(
    const internalWavePointPatchVectorField& ptf,
    const DimensionedField<vector, pointMesh>& iF
)
:
    fixedValuePointPatchField<vector>(ptf, iF),
    amplitude_(ptf.amplitude_),
    omega_(ptf.omega_),
    phase_(ptf.phase_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void internalWavePointPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    const Time& t = db().time();

    vector displacement = vector(0.0,0.0,0.0);
    for (label jsc = 0; jsc < amplitude_.size(); ++jsc)
    {
        displacement +=
        amplitude_[jsc] * cos(omega_[jsc] * t.value() + phase_[jsc]);
    }

    Field<vector>::operator=(displacement);

    fixedValuePointPatchField<vector>::updateCoeffs();
}


void internalWavePointPatchVectorField::write(Ostream& os) const
{
    pointPatchField<vector>::write(os);
    os.writeEntry("amplitude", amplitude_);
    os.writeEntry("omega", omega_);
    os.writeEntry("phase", phase_);
    writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePointPatchTypeField
(
    pointPatchVectorField,
    oscillatingDisplacementPointPatchVectorField
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
