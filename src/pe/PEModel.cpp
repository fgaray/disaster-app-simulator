#include "PEModel.hpp"



static int tag_amount = 0;

double  PEModel::getCostTime(){
	double cost = MODEL_COST;
	return cost;
}

PEModel::PEModel():PE(){
	this->precision = 0.5;
  this->tiempo_final = 0;
  this->terminados = 0;
}

std::vector<std::tuple<PEName, MessagePE>> PEModel::nextPE(MessagePE message){
	if (message.getTag())
	{
		std::cout << "flag tag " <<tag_amount<<std::endl;
		tag_amount++;
		if (tag_amount == MODEL_PRECISION)
		{
			if(this->precision >= 0.5 && this->precision < 0.7){

				std::cout << "flag precision"<<std::endl;
				this->precision = this->precision + VAR_PRECISION_1;
				tag_amount = 0;

			}
			if(this->precision >= 0.7 && this->precision <= 0.8){

				std::cout << "flag precision"<<std::endl;
				this->precision = this->precision + VAR_PRECISION_2;
				tag_amount = 0;

			}
			else{
				std::cout << "flag precision"<<std::endl;
				this->precision = this->precision + VAR_PRECISION_3;
				tag_amount = 0;

			}
			
		}
    this->terminados++;
    this->tiempo_final = currentTime;
		return {};
	}
	else{
		//envía el mismo mensaje sin modificar a PEAssembler
		return {std::make_tuple(PEName::PEFilter, message)};
	}

}


PEName PEModel::getName(){
  return PEName::PEModel;
}

double PEModel::getPrecision(){
	return this->precision;
}


double PEModel::getThroughput(){
  return (double)this->terminados / (double)this->tiempo_final;
}


unsigned int PEModel::getTotalMensajes(){
  return this->terminados;
}


double PEModel::getTotalMensajesTiempo(){
  return this->tiempo_final;
}
