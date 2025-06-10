// services/contentful.js
import { createClient } from 'contentful';

const client = createClient({
  space: import.meta.env.VITE_CONTENTFUL_SPACE_ID,
  accessToken: import.meta.env.VITE_CONTENTFUL_CDN_TOKEN,
});

export function getEquipamentos() {
  return client.getEntries({ content_type: 'equipamento' });
}
