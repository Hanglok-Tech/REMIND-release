#pragma once
#include <QMap>

enum TypeOperativeFile {
    ImageResult,
    DigitalBody,
    ImageSource,
    PostReference
};

const QMap<TypeOperativeFile, QString> TypeOperativeFileNames{
    {TypeOperativeFile::ImageResult, "PreoperativeFileInfo_ctResult"},
    {TypeOperativeFile::DigitalBody, "PreoperativeFileInfo_digitalBody"},
    {TypeOperativeFile::ImageSource, "PreoperativeFileInfo_ctSource"},
    {TypeOperativeFile::PostReference, "PostoperativeFileInfo_reference"}
};

enum TypeOperativeLesion {
    actual,
    plan
};

const QMap<TypeOperativeLesion, QString> TypeOperativeLesionNames{
    {TypeOperativeLesion::actual, "PreoperativeLesionInfo_actual"},
    {TypeOperativeLesion::plan, "PreoperativeLesionInfo_plan"}
};

enum TypeBodyPart
{
    defult,
    Bone,
    Liver,
    LiverTumor,
    Spleen,
    RightKidney,
    LeftKidney,
    Gallbladder,
    Esophagus,
    Stomach,
    Aorta,
    InferiorVenaCava,
    PortalVeinAndSplenicVein,
    Pancreas,
    RightAdrenalGland,
    LeftAdrenalGland,
    HepaticVessel,
    SkinCutted,

};

enum TypeSourceImage
{
    CT = 0,
    MRI = 1,
    UltraSound = 2,
    X_ray = 3
};

enum TypeNeedleRoutProperty : uint8_t
{
    OutSideBody = 0,
    ControlFocus = 1,
    ReadyPosition = 2,
    InnerBody = 3,
    InsertPosition = 4,
};
