//
// Created by fred on 1/10/22.
//

#include "shape.h"
#define I2I(x,y) int(x)*MatrixSize_x+int(y)
#define I2I_OBS(x,y) int(x)*OBSMatrixSize_x+int(y)

Shape ::Shape() {
    // TODO Ajouter les paramètres du Construct
}

Shape ::~Shape(){

}


    // TODO lire le fichier shape et attribuer une target selon l'id
    // TODO
void Shape ::Init(TConfigurationNode &t_tree) {
    // TODO init les params
}

void CArk::Reset() {
    // TODO voir si ce code est necc
    m_messaging_counter = 0;
}

/**
 *
 */
void Shape::read_target(){
    string filename("/home/fred/argos3-kilobot/u_letter.txt");
    vector<string> lines;
    string line;
    int nbLine = 0;

    ifstream input_file(filename);

    if(!input_file.is_open()){
        cerr << ERROR << endl;
        return EXIT_FAILURE;
    }

    while(getline(input_file, line)){
        lines.push_back(line);
        nbLines++;
    }
    cout << "taille d'une ligne : " << line.size() << endl;
    cout << "nbline : " << nbLines << endl;


}

void Shape::PreStep() {
    // TODO Ecrire ce code qui sera lancé avant chaque LOOP
    // TODO vérifier quand cette fonction est appelée
}

void Shape::PostStep() {
    // TODO Ecrire les résultats dans un fichier
}

void Shape::GetKilobotsEntities(){

    //Go through all the robots in the environment and create a vector of pointers on their entities
    CSpace::TMapPerType& kilobots_map = CSimulator::GetInstance().GetSpace().GetEntitiesByType("kilobot");

    for(CSpace::TMapPerType::iterator it = kilobots_map.begin(); it != kilobots_map.end();++it){
        m_KilobotsEntities.push_back(any_cast<CKilobotEntity*>(it->second));
    }
}

/****************************************/
/****************************************/

CVector2 Shape::GetKilobotPosition(CKilobotEntity* kilobot_entity){
    CVector3 pos3D = kilobot_entity->GetEmbodiedEntity().GetOriginAnchor().Position;
    //std::cout << "uid: " << kilo_uid << " - pos_X: " << pos3D.GetX() << " - pos_Y: " << pos3D.GetY() << std::endl;
    return CVector2(pos3D.GetX(), pos3D.GetY());
}


CRadians Shape::GetKilobotOrientation(CKilobotEntity* kilobot_entity){
    CRadians cZAngle;
    CRadians cYAngle;
    CRadians cXAngle;
    CQuaternion cQuaternion = kilobot_entity->GetEmbodiedEntity().GetOriginAnchor().Orientation;
    cQuaternion.ToEulerAngles(cZAngle,cYAngle, cXAngle);
    return cZAngle;
}

UInt16 Shape::GetKilobotId(CKilobotEntity *kilobot_entity){
    std::string entity_id((kilobot_entity)->GetControllableEntity().GetController().GetId());
    return std::stoul(entity_id.substr(2));
}

/****************************************/
/****************************************/

CColor CArk::GetKilobotLedColor(CKilobotEntity *kilobot_entity){
    return kilobot_entity->GetLEDEquippedEntity().GetLED(0).GetColor();
}


// TODO ecrire la fct get_message_to_send
/*
 * La fct devra envoyer:
 *  - la pos actuelle
 *  - le wp prevu
 *  - le prochain wp validé
 *  - la target
 *  -
 */

//void Shape::GetOptions(TConfigurationNode& t_tree){
//
//    TConfigurationNodeIterator itOptions;
//    for(itOptions=itOptions.begin(&t_tree);
//        itOptions!=itOptions.end();
//        ++itOptions){
//        if(itOptions->Value()=="option") {
//            AddOption(*itOptions);
//        }
//    }
//}
//
//
///****************************************/
///****************************************/
//
//void Shape::AddOption(TConfigurationNode& t_node){
//    FoodClass newFood;
//    GetNodeAttribute(t_node, "id", newFood.id);
//    if (newFood.id < 0) return;
//    GetNodeAttribute(t_node, "quality", newFood.quality);
//    GetNodeAttribute(t_node, "position", newFood.position);
//    GetNodeAttribute(t_node, "radius", newFood.radius);
//    GetNodeAttribute(t_node, "color", newFood.colour);
//    foodVector.push_back(newFood);
//}


