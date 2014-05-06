var bufferpack = require('bufferpack');

var PACKET_HEADER_SIZE = 2;
var PACKET_ITEM_SIZE = 7;

function Packet(buffer) {
  // resolve the buffer
  this.size = bufferpack.unpack('<h', buffer, 0);

  var items = [], item;

  for (var idx = 0; idx < this.size; idx ++) {
    item = bufferpack.unpack('<HB', buffer, PACKET_HEADER_SIZE + idx * PACKET_ITEM_SIZE);
    item = {
      type: item[0],
      data_type: item[1]
    };
    item.data = bufferpack.unpack('<' + item_pack_mapping[item.data_type], buffer, PACKET_HEADER_SIZE + idx * PACKET_ITEM_SIZE + 3);
    items.push(item);
  }

  this.items = items;

  this.log = function () {
    console.log('bumble packet -------');
    console.log('size:\t\t' + this.size);
    console.log('items:');
    items.forEach(function (item, index) {
      console.log('[' + index + ']\t\t' + sensor_mapping[item.type] + ' ' + item_pack_mapping[item.data_type] + ' ' + item.data);
    });
  };
}

var Sensor = {
  Temperature:    0x0001,
  Humidity:       0x0002,
  Barometric:     0x0003,
  Luminosity:     0x0010
};

var sensor_mapping = {
  0x0001: 'Temperature',
  0x0002: 'Humidity',
  0x0003: 'Barometric',
  0x0010: 'Luminosity'
};

var Item = {
  Signed:         0,
  Unsigned:       1,
  Float:          2
};

var item_pack_mapping = {};
item_pack_mapping[Item.Signed] = 'l';
item_pack_mapping[Item.Unsigned] = 'L';
item_pack_mapping[Item.Float] = 'f';

module.exports.Packet = Packet;
module.exports.Sensor = Sensor;
module.exports.Item = Item;
