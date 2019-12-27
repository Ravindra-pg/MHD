 Info<< "Reading transportProperties\n" << endl;
 IOdictionary transportProperties
 (
 IOobject
 (
 "transportProperties",
 runTime.constant(),
 mesh,
 IOobject::MUST_READ_IF_MODIFIED,
 IOobject::NO_WRITE
 )
 );

 Info<< "Reading electromagneticProperties\n" << endl;
 //Additional dictionary for magnetic field definition
 IOdictionary electromagneticProperties
 (
 IOobject
 (
 "electromagneticProperties",
 runTime.constant(),
 mesh,
 IOobject::MUST_READ_IF_MODIFIED,
 IOobject::NO_WRITE
 )
 );
 
 //Density
 dimensionedScalar rho
 (
 "rho",
 dimDensity,
 transportProperties.lookup("rho")
 );
 //Electrical conductivity
 dimensionedScalar sigma
 (
 "sigma",
 dimensionSet(-1, -3, 3, 0, 0, 2, 0),
 transportProperties.lookup("sigma")
 );
 //Magnetic field
 dimensionedVector B0
 (
 "B0",
 dimensionSet(1, 0, -2, 0, 0, -1, 0),
 electromagneticProperties.lookup("B0")
 );

 Info<< "Reading field p\n" << endl;
 volScalarField p
 (
     IOobject
     (
         "p",
         runTime.timeName(),
         mesh,
         IOobject::MUST_READ,
         IOobject::AUTO_WRITE
     ),
     mesh
 );
 
 
 Info<< "Reading field U\n" << endl;
 volVectorField U
 (
     IOobject
     (
         "U",
         runTime.timeName(),
         mesh,
         IOobject::MUST_READ,
         IOobject::AUTO_WRITE
     ),
     mesh
 );
 
 
 #include "createPhi.H"
 //Electric potential field
 Info<< "Reading field PotE\n" << endl;
 volScalarField PotE
 (
 IOobject
 (
 "PotE",
 runTime.timeName(),
 mesh,
 IOobject::MUST_READ,
 IOobject::AUTO_WRITE
 ),
 mesh
 );
 
 singlePhaseTransportModel fluid(U, phi);
 
 
 //Pressure reference point
 label pRefCell = 0;
 scalar pRefValue = 0.0;
 setRefCell(p, mesh.solutionDict().subDict("PISO"), pRefCell, pRefValue);
 mesh.setFluxRequired(p.name());
 
 //Electric potential reference point
 label PotERefCell = 0;
 scalar PotERefValue = 0.0;
 setRefCell(PotE, mesh.solutionDict().subDict("PotE"), PotERefCell, PotERefValue);
 mesh.setFluxRequired(PotE.name());
