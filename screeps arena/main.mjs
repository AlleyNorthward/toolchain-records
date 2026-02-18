import { getTicks, getObjectsByPrototype } from 'game/utils';
import { Creep, Flag } from 'game/prototypes';
import { } from 'game/constants';

export function loop() {
  console.log('Current tick:', getTicks());

  var creeps = getObjectsByPrototype(Creep);
  var flags = getObjectsByPrototype(Flag);
  creeps[0].moveTo(flags[0]);
}
