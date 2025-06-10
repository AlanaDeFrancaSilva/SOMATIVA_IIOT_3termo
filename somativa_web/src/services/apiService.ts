// apiService.ts
import { createClient } from 'contentful-management';

const managementClient = createClient({
  accessToken: import.meta.env.VITE_CONTENTFUL_MANAGEMENT_TOKEN,
});

interface ManutencaoInput {
  equipamentoId: string;
  data: string;
  descricao: string;
  codigoManutencao?: string; // Campo opcional para o código
}

export async function criarManutencao({
  equipamentoId,
  data,
  descricao,
  codigoManutencao, // Inclua o código aqui
}: ManutencaoInput) {
  const space = await managementClient.getSpace(import.meta.env.VITE_CONTENTFUL_SPACE_ID);
  const environment = await space.getEnvironment('master');

  const fields: any = { // Use 'any' para permitir campos opcionais
    equipamento: {
      'en-US': {
        sys: {
          type: 'Link',
          linkType: 'Entry',
          id: equipamentoId,
        },
      },
    },
    data: {
      'en-US': data,
    },
    descricao: {
      'en-US': descricao,
    },
  };

  if (codigoManutencao) { // Adicione o campo 'codigoManutencao' apenas se tiver um valor
    fields.codigoManutencao = { 'en-US': codigoManutencao };
  }

  const manutencao = await environment.createEntry('manut', { fields });

  await manutencao.publish();
}