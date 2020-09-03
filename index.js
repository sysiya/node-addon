const addon = require('bindings')('addon');

console.log(addon);

addon.say('Hello, 世界！');

addon.say((message) => console.log('Hello, Callback.' + message));

addon.say(1000).then((data) => console.log('Promise: ', data));

try {
  addon.say(null);
} catch (err) {
  console.error(err);
}
