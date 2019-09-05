/*气压采集
 * 传感器读取ADC0 的值，取高位和低位，通过串口透传出去
 * 73 00 0C 01 74 F4  其中73是标志位，00 0c 是十六进制设备ID ,01 74 是十六进制模拟量的值，F4是和校验
 */
unsigned int sensor_leiwei=0;  //气压传感器
unsigned int leiwei_id=12;    //设备ID
void setup() {
Serial.begin(9600);
}

void loop() {

 //列尾的设备序号
 byte leiwei_id_lowbyte=lowByte(leiwei_id);   //取低位，值最大不能超过65535
 byte leiwei_id_highbyte=highByte(leiwei_id); //取高位
// Serial.write(leiwei_id_highbyte);
// Serial.write(leiwei_id_lowbyte);
 
 //列尾的气压值
 sensor_leiwei = analogRead(A0);  //读取A0模拟值
 byte sensor_leiwei_lowbyte=lowByte(sensor_leiwei);    //取低位，值最大不能超过65535
 byte sensor_leiwei_highbyte=highByte(sensor_leiwei);  //取高位
// Serial.write(sensor_leiwei_highbyte);
// Serial.write(sensor_leiwei_lowbyte);
 
 unsigned char senddata[]={0x73,leiwei_id_highbyte,leiwei_id_lowbyte, sensor_leiwei_highbyte,sensor_leiwei_lowbyte,0x0ff&(0x73+leiwei_id_highbyte+leiwei_id_lowbyte+sensor_leiwei_highbyte+sensor_leiwei_lowbyte)};   //组合数据，最后和校验
 Serial.write(senddata,6); // 串口输出73 00 0C 01 74 F4 
 delay(5000);  
}
