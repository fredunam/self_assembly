//
// Created by fred on 1/10/22.
//
#include <iostream>

#include "shape.h"
#define I2I(x,y) int(x)*MatrixSize_x+int(y)
#define I2I_OBS(x,y) int(x)*OBSMatrixSize_x+int(y)

Shape::Shape():CLoopFunctions(),m_cSimulator(GetSimulator()), m_iCellsPerMetre(100),m_iCellsPerMetreOBS(100), m_ohcEmbodiedEntity(CEmbodiedEntity(NULL, "ohc_body", CVector3(0,0,1), CQuaternion())),
               m_cCommAnchor(m_ohcEmbodiedEntity.AddAnchor("comm", CVector3(0,0,0))),m_tx_flag(false), m_messaging_counter(0),m_floor_counter(0), m_update_matrix_timesteps(0), MatrixSize_x(0), MatrixSize_y(0),
               floorMatrix(0),OBSMatrixSize_x(0), OBSMatrixSize_y(0), obstacle_Matrix(0),m_showObstacleAvoidanceArea(false), maxPheroLimit(std::numeric_limits<float>::max()), evaporation_rate(0.05),
               diffusion_rate(0.02), pheromone_amount(250),m_obstacle_avoidance_range(0.05),m_Vmax(0) {
    // TODO Ajouter les paramètres du Construct
}

Shape::~Shape(){

}


    // TODO lire le fichier shape et attribuer une target selon l'id
    // TODO
void Shape::Init(TConfigurationNode &t_tree) {
    // TODO init les params
}

void Shape::Reset() {
    // TODO voir si ce code est necc
    m_messaging_counter = 0;
}

/**
 *
 */
void Shape::read_target(){
    ifstream input_file("/home/fred/argos3-kilobot/u_letter.txt");
    vector<string> lines;
    string line;
    int nbLine = 0;

    if(input_file){
        while(getline(input_file, line)){
            cout << line << endl;
            nbLine ++;
        }
    }

    else{
        cout << "ERROR: Impossible to read file" << endl;
    }

    //cout << "il y a " << nbLine << "dans ce fichier" << ednl;

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

CColor Shape::GetKilobotLedColor(CKilobotEntity *kilobot_entity){
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


