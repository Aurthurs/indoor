import { supabase } from './supabase'

async function listTables() {
  // 查询 information_schema 获取表列表
  const { data, error } = await supabase
    .from('information_schema.tables')
    .select('table_name, table_schema')
    .eq('table_schema', 'public')

  if (error) {
    console.error('查询表失败:', error)
    return
  }

  console.log('表列表:', data)
}

async function describeTable(tableName: string) {
  const { data, error } = await supabase
    .from('information_schema.columns')
    .select('column_name, data_type, is_nullable')
    .eq('table_name', tableName)
    .eq('table_schema', 'public')

  if (error) {
    console.error(`查询 ${tableName} 结构失败:`, error)
    return
  }

  console.log(`${tableName} 表结构:`, data)
}

listTables().then(() => {
  describeTable('user')
})
