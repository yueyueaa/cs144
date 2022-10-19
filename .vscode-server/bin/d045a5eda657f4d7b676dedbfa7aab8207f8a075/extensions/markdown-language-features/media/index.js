(()=>{var De=(e,t)=>()=>(t||e((t={exports:{}}).exports,t),t.exports);var Ne=De((wt,Le)=>{var Se="Expected a function",Ee=0/0,Ye="[object Symbol]",$e=/^\s+|\s+$/g,Ke=/^[-+]0x[0-9a-f]+$/i,Je=/^0b[01]+$/i,Qe=/^0o[0-7]+$/i,Ze=parseInt,et=typeof global=="object"&&global&&global.Object===Object&&global,tt=typeof self=="object"&&self&&self.Object===Object&&self,nt=et||tt||Function("return this")(),rt=Object.prototype,it=rt.toString,at=Math.max,ot=Math.min,ce=function(){return nt.Date.now()};function st(e,t,n){var r,i,a,s,c,u,g=0,b=!1,v=!1,w=!0;if(typeof e!="function")throw new TypeError(Se);t=Ae(t)||0,J(n)&&(b=!!n.leading,v="maxWait"in n,a=v?at(Ae(n.maxWait)||0,t):a,w="trailing"in n?!!n.trailing:w);function h(m){var S=r,k=i;return r=i=void 0,g=m,s=e.apply(k,S),s}function E(m){return g=m,c=setTimeout(N,t),b?h(m):s}function A(m){var S=m-u,k=m-g,p=t-S;return v?ot(p,a-k):p}function O(m){var S=m-u,k=m-g;return u===void 0||S>=t||S<0||v&&k>=a}function N(){var m=ce();if(O(m))return I(m);c=setTimeout(N,A(m))}function I(m){return c=void 0,w&&r?h(m):(r=i=void 0,s)}function U(){c!==void 0&&clearTimeout(c),g=0,r=u=i=c=void 0}function q(){return c===void 0?s:I(ce())}function D(){var m=ce(),S=O(m);if(r=arguments,i=this,u=m,S){if(c===void 0)return E(u);if(v)return c=setTimeout(N,t),h(u)}return c===void 0&&(c=setTimeout(N,t)),s}return D.cancel=U,D.flush=q,D}function lt(e,t,n){var r=!0,i=!0;if(typeof e!="function")throw new TypeError(Se);return J(n)&&(r="leading"in n?!!n.leading:r,i="trailing"in n?!!n.trailing:i),st(e,t,{leading:r,maxWait:t,trailing:i})}function J(e){var t=typeof e;return!!e&&(t=="object"||t=="function")}function ct(e){return!!e&&typeof e=="object"}function dt(e){return typeof e=="symbol"||ct(e)&&it.call(e)==Ye}function Ae(e){if(typeof e=="number")return e;if(dt(e))return Ee;if(J(e)){var t=typeof e.valueOf=="function"?e.valueOf():e;e=J(t)?t+"":t}if(typeof e!="string")return e===0?e:+e;e=e.replace($e,"");var n=Je.test(e);return n||Qe.test(e)?Ze(e.slice(2),n?2:8):Ke.test(e)?Ee:+e}Le.exports=lt});var ge="code-line",ne=(()=>{let e,t=-1;return n=>{if(!e||n!==t){t=n,e=[{element:document.body,line:0}];for(let r of document.getElementsByClassName(ge)){let i=+r.getAttribute("data-line");isNaN(i)||(r.tagName==="CODE"&&r.parentElement&&r.parentElement.tagName==="PRE"?e.push({element:r.parentElement,line:i}):r.tagName==="UL"||r.tagName==="OL"||e.push({element:r,line:i}))}console.log(e)}return e}})();function re(e,t){let n=Math.floor(e),r=ne(t),i=r[0]||null;for(let a of r){if(a.line===n)return{previous:a,next:void 0};if(a.line>n)return{previous:i,next:a};i=a}return{previous:i}}function ke(e,t){let n=ne(t),r=e-window.scrollY,i=-1,a=n.length-1;for(;i+1<a;){let u=Math.floor((i+a)/2),g=F(n[u]);g.top+g.height>=r?a=u:i=u}let s=n[a],c=F(s);return a>=1&&c.top>r?{previous:n[i],next:s}:a>1&&a<n.length&&c.top+c.height>r?{previous:s,next:n[a+1]}:{previous:s}}function F({element:e}){let t=e.getBoundingClientRect(),n=e.querySelector(`.${ge}`);if(n){let r=n.getBoundingClientRect(),i=Math.max(1,r.top-t.top);return{top:t.top,height:i}}return t}function Y(e,t,n){if(!n.settings?.scrollPreviewWithEditor)return;if(e<=0){window.scroll(window.scrollX,0);return}let{previous:r,next:i}=re(e,t);if(!r)return;let a=0,s=F(r),c=s.top;if(i&&i.line!==r.line){let u=(e-r.line)/(i.line-r.line),g=i.element.getBoundingClientRect().top-c;a=c+u*g}else{let u=e-Math.floor(e);a=c+s.height*u}a=Math.abs(a)<1?Math.sign(a):a,window.scroll(window.scrollX,Math.max(1,window.scrollY+a))}function ie(e,t){let{previous:n,next:r}=ke(e,t);if(n){let i=F(n),a=e-window.scrollY-i.top;if(r){let s=a/(F(r).top-i.top);return n.line+s*(r.line-n.line)}else{let s=a/i.height;return n.line+s}}return null}function me(e,t){return ne(t).find(n=>n.element.id===e)}var ae=class{onDidChangeTextEditorSelection(t,n){let{previous:r}=re(t,n);this._update(r&&r.element)}_update(t){this._unmarkActiveElement(this._current),this._markActiveElement(t),this._current=t}_unmarkActiveElement(t){!t||(t.className=t.className.replace(/\bcode-active-line\b/g,""))}_markActiveElement(t){!t||(t.className+=" code-active-line")}};function pe(e){document.readyState==="loading"||document.readyState==="uninitialized"?document.addEventListener("DOMContentLoaded",e):e()}var ve=(e,t)=>new class{postMessage(n,r){e.postMessage({type:n,source:t.settings.source,body:r})}};function oe(e){let t=document.getElementById("vscode-markdown-preview-data");if(t){let n=t.getAttribute(e);if(n)return JSON.parse(n)}throw new Error(`Could not load data for ${e}`)}var se=class{constructor(){this._settings=oe("data-settings")}get settings(){return this._settings}updateSettings(t){this._settings=t}};var he=11;function Re(e,t){var n=t.attributes,r,i,a,s,c;if(!(t.nodeType===he||e.nodeType===he)){for(var u=n.length-1;u>=0;u--)r=n[u],i=r.name,a=r.namespaceURI,s=r.value,a?(i=r.localName||i,c=e.getAttributeNS(a,i),c!==s&&(r.prefix==="xmlns"&&(i=r.name),e.setAttributeNS(a,i,s))):(c=e.getAttribute(i),c!==s&&e.setAttribute(i,s));for(var g=e.attributes,b=g.length-1;b>=0;b--)r=g[b],i=r.name,a=r.namespaceURI,a?(i=r.localName||i,t.hasAttributeNS(a,i)||e.removeAttributeNS(a,i)):t.hasAttribute(i)||e.removeAttribute(i)}}var $,_e="http://www.w3.org/1999/xhtml",y=typeof document=="undefined"?void 0:document,Be=!!y&&"content"in y.createElement("template"),Ue=!!y&&y.createRange&&"createContextualFragment"in y.createRange();function He(e){var t=y.createElement("template");return t.innerHTML=e,t.content.childNodes[0]}function Ie(e){$||($=y.createRange(),$.selectNode(y.body));var t=$.createContextualFragment(e);return t.childNodes[0]}function Fe(e){var t=y.createElement("body");return t.innerHTML=e,t.childNodes[0]}function je(e){return e=e.trim(),Be?He(e):Ue?Ie(e):Fe(e)}function K(e,t){var n=e.nodeName,r=t.nodeName,i,a;return n===r?!0:(i=n.charCodeAt(0),a=r.charCodeAt(0),i<=90&&a>=97?n===r.toUpperCase():a<=90&&i>=97?r===n.toUpperCase():!1)}function Ve(e,t){return!t||t===_e?y.createElement(e):y.createElementNS(t,e)}function We(e,t){for(var n=e.firstChild;n;){var r=n.nextSibling;t.appendChild(n),n=r}return t}function le(e,t,n){e[n]!==t[n]&&(e[n]=t[n],e[n]?e.setAttribute(n,""):e.removeAttribute(n))}var be={OPTION:function(e,t){var n=e.parentNode;if(n){var r=n.nodeName.toUpperCase();r==="OPTGROUP"&&(n=n.parentNode,r=n&&n.nodeName.toUpperCase()),r==="SELECT"&&!n.hasAttribute("multiple")&&(e.hasAttribute("selected")&&!t.selected&&(e.setAttribute("selected","selected"),e.removeAttribute("selected")),n.selectedIndex=-1)}le(e,t,"selected")},INPUT:function(e,t){le(e,t,"checked"),le(e,t,"disabled"),e.value!==t.value&&(e.value=t.value),t.hasAttribute("value")||e.removeAttribute("value")},TEXTAREA:function(e,t){var n=t.value;e.value!==n&&(e.value=n);var r=e.firstChild;if(r){var i=r.nodeValue;if(i==n||!n&&i==e.placeholder)return;r.nodeValue=n}},SELECT:function(e,t){if(!t.hasAttribute("multiple")){for(var n=-1,r=0,i=e.firstChild,a,s;i;)if(s=i.nodeName&&i.nodeName.toUpperCase(),s==="OPTGROUP")a=i,i=a.firstChild;else{if(s==="OPTION"){if(i.hasAttribute("selected")){n=r;break}r++}i=i.nextSibling,!i&&a&&(i=a.nextSibling,a=null)}e.selectedIndex=n}}},j=1,qe=11,ye=3,Te=8;function R(){}function Xe(e){if(e)return e.getAttribute&&e.getAttribute("id")||e.id}function ze(e){return function(n,r,i){if(i||(i={}),typeof r=="string")if(n.nodeName==="#document"||n.nodeName==="HTML"||n.nodeName==="BODY"){var a=r;r=y.createElement("html"),r.innerHTML=a}else r=je(r);var s=i.getNodeKey||Xe,c=i.onBeforeNodeAdded||R,u=i.onNodeAdded||R,g=i.onBeforeElUpdated||R,b=i.onElUpdated||R,v=i.onBeforeNodeDiscarded||R,w=i.onNodeDiscarded||R,h=i.onBeforeElChildrenUpdated||R,E=i.childrenOnly===!0,A=Object.create(null),O=[];function N(d){O.push(d)}function I(d,l){if(d.nodeType===j)for(var o=d.firstChild;o;){var f=void 0;l&&(f=s(o))?N(f):(w(o),o.firstChild&&I(o,l)),o=o.nextSibling}}function U(d,l,o){v(d)!==!1&&(l&&l.removeChild(d),w(d),I(d,o))}function q(d){if(d.nodeType===j||d.nodeType===qe)for(var l=d.firstChild;l;){var o=s(l);o&&(A[o]=l),q(l),l=l.nextSibling}}q(n);function D(d){u(d);for(var l=d.firstChild;l;){var o=l.nextSibling,f=s(l);if(f){var L=A[f];L&&K(l,L)?(l.parentNode.replaceChild(L,l),S(L,l)):D(l)}else D(l);l=o}}function m(d,l,o){for(;l;){var f=l.nextSibling;(o=s(l))?N(o):U(l,d,!0),l=f}}function S(d,l,o){var f=s(l);f&&delete A[f],!(!o&&(g(d,l)===!1||(e(d,l),b(d),h(d,l)===!1)))&&(d.nodeName!=="TEXTAREA"?k(d,l):be.TEXTAREA(d,l))}function k(d,l){var o=l.firstChild,f=d.firstChild,L,C,H,z,M;e:for(;o;){for(z=o.nextSibling,L=s(o);f;){if(H=f.nextSibling,o.isSameNode&&o.isSameNode(f)){o=z,f=H;continue e}C=s(f);var G=f.nodeType,P=void 0;if(G===o.nodeType&&(G===j?(L?L!==C&&((M=A[L])?H===M?P=!1:(d.insertBefore(M,f),C?N(C):U(f,d,!0),f=M):P=!1):C&&(P=!1),P=P!==!1&&K(f,o),P&&S(f,o)):(G===ye||G==Te)&&(P=!0,f.nodeValue!==o.nodeValue&&(f.nodeValue=o.nodeValue))),P){o=z,f=H;continue e}C?N(C):U(f,d,!0),f=H}if(L&&(M=A[L])&&K(M,o))d.appendChild(M),S(M,o);else{var te=c(o);te!==!1&&(te&&(o=te),o.actualize&&(o=o.actualize(d.ownerDocument||y)),d.appendChild(o),D(o))}o=z,f=H}m(d,f,C);var fe=be[d.nodeName];fe&&fe(d,l)}var p=n,X=p.nodeType,ue=r.nodeType;if(!E){if(X===j)ue===j?K(n,r)||(w(n),p=We(n,Ve(r.nodeName,r.namespaceURI))):p=r;else if(X===ye||X===Te){if(ue===X)return p.nodeValue!==r.nodeValue&&(p.nodeValue=r.nodeValue),p;p=r}}if(p===r)w(n);else{if(r.isSameNode&&r.isSameNode(p))return;if(S(p,r,E),O)for(var Z=0,Oe=O.length;Z<Oe;Z++){var ee=A[O[Z]];ee&&U(ee,ee.parentNode,!1)}}return!E&&p!==n&&n.parentNode&&(p.actualize&&(p=p.actualize(n.ownerDocument||y)),n.parentNode.replaceChild(p,n)),p}}var Ge=ze(Re),we=Ge;var xe=Ne(),_=0,Ce=new ae,T=new se,x=0,Q=T.settings.source,V=acquireVsCodeApi(),Me=V.getState(),B={...typeof Me=="object"?Me:{},...oe("data-state")};V.setState(B);var W=ve(V,T);window.cspAlerter.setPoster(W);window.styleLoadingMonitor.setPoster(W);function de(e){let t=document.getElementsByTagName("img");if(t.length>0){let n=Array.from(t,r=>r.complete?Promise.resolve():new Promise(i=>{r.addEventListener("load",()=>i()),r.addEventListener("error",()=>i())}));Promise.all(n).then(()=>setTimeout(e,0))}else setTimeout(e,0)}pe(()=>{let e=B.scrollProgress;if(typeof e=="number"&&!T.settings.fragment){de(()=>{_+=1,window.scrollTo(0,e*document.body.clientHeight)});return}T.settings.scrollPreviewWithEditor&&de(()=>{if(T.settings.fragment){B.fragment=void 0,V.setState(B);let t=me(T.settings.fragment,x);t&&(_+=1,Y(t.line,x,T))}else isNaN(T.settings.line)||(_+=1,Y(T.settings.line,x,T))}),typeof T.settings.selectedLine=="number"&&Ce.onDidChangeTextEditorSelection(T.settings.selectedLine,x)});var ut=(()=>{let e=xe(t=>{_+=1,de(()=>Y(t,x,T))},50);return t=>{isNaN(t)||(B.line=t,e(t))}})();window.addEventListener("resize",()=>{_+=1,Pe()},!0);window.addEventListener("message",async e=>{switch(e.data.type){case"onDidChangeTextEditorSelection":e.data.source===Q&&Ce.onDidChangeTextEditorSelection(e.data.line,x);return;case"updateView":e.data.source===Q&&ut(e.data.line);return;case"updateContent":{let t=document.querySelector(".markdown-body"),r=new DOMParser().parseFromString(e.data.content,"text/html");for(let i of Array.from(r.querySelectorAll("meta")))i.hasAttribute("http-equiv")&&i.remove();if(e.data.source!==Q)t.replaceWith(r.querySelector(".markdown-body")),Q=e.data.source;else{let i=(c,u)=>{if(c.isEqualNode(u))return!0;if(c.tagName!==u.tagName||c.textContent!==u.textContent)return!1;let g=c.attributes,b=u.attributes;if(g.length!==b.length)return!1;for(let h=0;h<g.length;++h){let E=g[h],A=b[h];if(E.name!==A.name||E.value!==A.value&&E.name!=="data-line")return!1}let v=Array.from(c.children),w=Array.from(u.children);return v.length===w.length&&v.every((h,E)=>i(h,w[E]))},a=r.querySelector(".markdown-body"),s=a.querySelectorAll("link");for(let c of s)c.remove();a.prepend(...s),we(t,a,{childrenOnly:!0,onBeforeElUpdated:(c,u)=>{if(i(c,u)){let g=c.querySelectorAll("[data-line]"),b=c.querySelectorAll("[data-line]");g.length!==b.length&&console.log("unexpected line number change");for(let v=0;v<g.length;++v){let w=g[v],h=b[v];h&&w.setAttribute("data-line",h.getAttribute("data-line"))}return!1}return!0}})}++x,window.dispatchEvent(new CustomEvent("vscode.markdown.updateContent"));break}}},!1);document.addEventListener("dblclick",e=>{if(!T.settings.doubleClickToSwitchToEditor)return;for(let r=e.target;r;r=r.parentNode)if(r.tagName==="A")return;let t=e.pageY,n=ie(t,x);typeof n=="number"&&!isNaN(n)&&W.postMessage("didClick",{line:Math.floor(n)})});var ft=["http:","https:","mailto:","vscode:","vscode-insiders:"];document.addEventListener("click",e=>{if(!e)return;let t=e.target;for(;t;){if(t.tagName&&t.tagName==="A"&&t.href){if(t.getAttribute("href").startsWith("#"))return;let n=t.getAttribute("data-href");if(!n){if(ft.some(r=>t.href.startsWith(r)))return;n=t.getAttribute("href")}if(!/^[a-z\-]+:/i.test(n)){W.postMessage("openLink",{href:n}),e.preventDefault(),e.stopPropagation();return}return}t=t.parentNode}},!0);window.addEventListener("scroll",xe(()=>{if(Pe(),_>0)_-=1;else{let e=ie(window.scrollY,x);typeof e=="number"&&!isNaN(e)&&W.postMessage("revealLine",{line:e})}},50));function Pe(){B.scrollProgress=window.scrollY/document.body.clientHeight,V.setState(B)}})();
