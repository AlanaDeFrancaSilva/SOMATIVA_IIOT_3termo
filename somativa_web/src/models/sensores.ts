export class Dados {
  plant_1_HUM: number = 0;
  plant_1_TEMP: number = 0;

  plant_2_HUM: number = 0;
  plant_2_TEMP: number = 0;

  plant_3_HUM: number = 0;
  plant_3_TEMP: number = 0;

  plant_4_HUM: number = 0;
  plant_4_TEMP: number = 0;

  tanque_PH: number = 0;
  tanque_TEMP: number = 0;

  time: Date = new Date();
}

export class Manutencao {
  id: number = 0;
  equipamento: string = '';
  data: Date = new Date();
  descricao: string = ''
}
