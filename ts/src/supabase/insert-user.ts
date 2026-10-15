import { createClient } from '@supabase/supabase-js'
import 'dotenv/config'

const supabaseUrl = process.env.SUPABASE_URL!
const supabaseServiceKey = process.env.SUPABASE_SERVICE_ROLE_KEY!

const supabaseAdmin = createClient(supabaseUrl, supabaseServiceKey)

async function inspectTable() {
  // 尝试不带任何列，看是否能获取到数据或报错信息
  const { data, error } = await supabaseAdmin.from('user').select('*').limit(1)

  console.log('查询结果:', data)
  console.log('错误:', error)
}

inspectTable()
